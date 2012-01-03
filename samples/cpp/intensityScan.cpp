/*!
  \example intensityScan.cpp

  \brief Sample to get intensity data

  \author Satofumi KAMIMURA

  $Id: intensityScan.cpp 1737 2010-03-06 07:15:19Z satofumi $
*/

#include "UrgDevice.h"
#include "delay.h"
#include <SDL.h>
#include <cstdlib>
#include <cstdio>

using namespace qrk;
using namespace std;


int main(int argc, char *argv[])
{
  // Change the port name appropriately
#ifdef WINDOWS_OS
  const char device[] = "COM3";
#else
  const char device[] = "/dev/ttyACM0";
#endif

  UrgDevice urg;
  if (! urg.connect(device)) {
    printf("UrgDevice::connect: %s\n", urg.what());
    exit(1);
  }
  int scan_msec = urg.scanMsec();
  urg.setCaptureMode(IntensityCapture);

  enum {
    CaptureTimes = 10,
  };

  vector<long> data;
  vector<long> intensity_data;

  long previous_timestamp = 0;
  for (int i = 0; i < CaptureTimes; ++i) {
    long timestamp = 0;
    int data_n = urg.captureWithIntensity(data, intensity_data, &timestamp);
    if (data_n > 0) {
      int front_index = urg.rad2index(0.0);
      printf("%d: %ld [mm] (%ld), %ld [msec] (%ld)\n",
             i, data[front_index], intensity_data[front_index], timestamp,
             timestamp - previous_timestamp);
      previous_timestamp = timestamp;
    } else {
      --i;
      delay(scan_msec);
    }
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

/*!
  \example mdScan.cpp

  \brief Sample to get data using MD command

  \author Satofumi KAMIMURA

  $Id: mdScan.cpp 1737 2010-03-06 07:15:19Z satofumi $
*/

#include "UrgDevice.h"
#include "delay.h"
#include "ticks.h"
#include <cstdlib>
#include <cstdio>

using namespace qrk;
using namespace std;


//! main
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

#if 1
  // Set to MD mode to acquire data
  urg.setCaptureMode(AutoCapture);

#else
  // Mode to get distance data and intensity data
  urg.setCaptureMode(IntensityCapture);
  urg.setCaptureSkipLines(2);
#endif
  int scan_msec = urg.scanMsec();

#if 0
  // Set range of acquisition from the center to left 90 degree.
  // Set range of acquistion from center to right to 90 degree.
  // So In total it will be 180 degree.
  const double rad90 = 90.0 * M_PI / 180.0;
  urg.setCaptureRange(urg.rad2index(-rad90), urg.rad2index(rad90));
#endif

  int pre_timestamp = ticks();

  // Data is acquired continuously using MD command
  // but outputs data of specified number of times.
  enum { CaptureTimes = 10};
  urg.setCaptureTimes(CaptureTimes);
  for (int i = 0; i < CaptureTimes;) {
    long timestamp = 0;
    vector<long> data;

    // Get data
    int n = urg.capture(data, &timestamp);
    if (n <= 0) {
      delay(scan_msec);
      continue;
    }

    // Display
    printf("timestamp: %ld, (%ld), %ld\n",
           timestamp, ticks(), timestamp - pre_timestamp);
    pre_timestamp = timestamp;
#if 0
    for (int j = 0; j < n; ++j) {
      // The distance data that are less than urg_minDistance() are shown
      // as invalide values
      printf("%d:%ld, ", j, data[j]);
    }
    printf("\n");
#endif
    ++i;
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

/*!
  \example gdScan.cpp

  \brief Sample to get data using GD command

  \author Satofumi KAMIMURA

  $Id: gdScan.cpp 1932 2010-10-02 21:46:01Z satofumi $
*/

#include "UrgDevice.h"
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

  // Scans for the number of times specified as in GD command and outputs
  // the data.
  enum { CaptureTimes = 1 };
  for (int i = 0; i < CaptureTimes; ++i) {
    long timestamp = 0;
    vector<long> data;

    // Get the data
    int n = urg.capture(data, &timestamp);

    // Display
    printf("timestamp: %ld\n", timestamp);
    for (int j = 0; j < n; ++j) {
      // The distance data that are less than urg_minDistance() are shown as
      // invalide values
      printf("%d:%ld, ", j, data[j]); // index, length [mm]
    }
    printf("\n");
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

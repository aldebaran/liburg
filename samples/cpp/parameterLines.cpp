/*!
  \example parameterLines.cpp

  \brief Displays PP data

  \author Satofumi KAMIMURA

  $Id: parameterLines.cpp 1737 2010-03-06 07:15:19Z satofumi $
*/

#include "UrgDevice.h"
#include "RangeSensorParameter.h"
#include <cstdlib>
#include <cstdio>

using namespace qrk;


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

  // Display parameter information
  RangeSensorParameter parameters = urg.parameter();
  printf("model: %s\n", parameters.model.c_str());
  printf("distance_min: %ld\n", parameters.distance_min);
  printf("distance_max: %ld\n", parameters.distance_max);
  printf("area_total: %d\n", parameters.area_total);
  printf("area_min: %d\n", parameters.area_min);
  printf("area_max: %d\n", parameters.area_max);
  printf("area_front: %d\n", parameters.area_front);
  printf("scan_rpm: %d\n", parameters.scan_rpm);

#ifdef MSC
  getchar();
#endif

  return 0;
}

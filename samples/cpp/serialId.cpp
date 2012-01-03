/*!
  \example serialId.cpp

  \brief Displays serial ID of URG

  \author Satofumi KAMIMURA

  $Id: serialId.cpp 1737 2010-03-06 07:15:19Z satofumi $
*/

#include "UrgDevice.h"
#include "UrgUtils.h"
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

  printf("Serial ID: %ld\n", urgSerialId<UrgDevice>(&urg));

#ifdef MSC
  getchar();
#endif

  return 0;
}

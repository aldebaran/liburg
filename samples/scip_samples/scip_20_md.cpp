/*!
  \example scip_20_md.cpp

  \brief Get response of MD command

  \author Satofumi KAMIMURA

  $Id: scip_20_md.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "DetectOS.h"
#include "SerialDevice.h"
#include "ConnectionUtils.h"
#include "ScipUtils.h"
#include <cstdio>

using namespace qrk;


//! main
int main(int argc, char *argv[])
{
  // Change the port name appropriately
#if defined(WINDOWS_OS)
  const char device[] = "COM3";
#elif defined(LINUX_OS)
  const char device[] = "/dev/ttyACM0";
#else
  const char device[] = "/dev/tty.usbmodem1d11";
#endif

  SerialDevice con;
  if (! con.connect(device, 19200)) {
    printf("SerialDevice::connect: %s\n", con.what());
#if defined(WINDOWS_OS)
    printf("Hit return key.\n");
    getchar();
#endif
    exit(1);
  }

  // Call SCIP2.0 and neglect the response
  enum { Timeout = 200 };
  con.send("SCIP2.0\n", 8);
  skip(&con, Timeout);

  // Send MD command
  //
  // MD or MS
  // 0000  should be greater than AMIN value (AMIN: refer PP command)
  // 0725  should be less than AMAX value (AMAX: refer PP command)
  // 01    cluster value
  // 0     scan_interval
  // 05    number of scan. 00 means infinity
  //
  // Actually, returned response will come into effect at the next cycle after
  // the command is issued. This is because, at first cycle, the laser will
  // be in OFF state.
  con.send("MD0000072501005\n", 16);

  // Display received data
  enum {
    LineMax = 64 + 1 + 1,
    URG_04LX_MAX = 725,
    TryTimes = 5,
  };
  char buffer[LineMax];
  int n;
  for (int j = 0; j < TryTimes; ++j) {
    while ((n = readline(&con, buffer, LineMax, Timeout)) > 0) {
      printf("%s\n", buffer);
    }
    printf("\n");

    // To get data of 2 scans, stop acquisition of data using "QT" command.
    if (j >= 1) {
      con.send("QT\n", 3);
    }
  }
  printf("\n");

  // Decoding of data is omitted.
  // After echo back and status, distance data follows continuously.
  // The other basic remains same as "GD" command response.

#if defined(WINDOWS_OS)
  printf("Hit return key.\n");
  getchar();
#endif

  return 0;
}

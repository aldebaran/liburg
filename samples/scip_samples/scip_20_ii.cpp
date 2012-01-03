/*!
  \example scip_20_ii.cpp

  \brief Get response of II command

  \author Satofumi KAMIMURA

  $Id: scip_20_ii.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "SerialDevice.h"
#include "DetectOS.h"
#include "ConnectionUtils.h"
#include <stdio.h>

using namespace qrk;


//! main
int main(int argc, char *argv[]) {

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

  // Call Scip2.0 and neglect the response.
  enum { Timeout = 200 };
  con.send("SCIP2.0\n", 8);
  skip(&con, Timeout);

  // Send "II" command
  con.send("II\n", 3);

  // Display the received data
  enum { LineMax = 64 + 1 };
  char buffer[LineMax];
  int n;
  while ((n = readline(&con, buffer, LineMax, Timeout)) > 0) {
    printf("%s\n", buffer);
  }

#if defined(WINDOWS_OS)
  printf("Hit return key.\n");
  getchar();
#endif

  return 0;
}

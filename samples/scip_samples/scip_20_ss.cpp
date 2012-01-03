/*!
  \example scip_20_ss.cpp

  \brief Execution sample of "SS" of SCIP2.0

  \author Satofumi KAMIMURA

  $Id: scip_20_ss.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "SerialDevice.h"
#include "DetectOS.h"
#include "ConnectionUtils.h"
#include <cstdio>

using namespace qrk;


//! main
int main(int argc, char *argv[])
{
  // Change the port name appropriately
#if defined(WINDOWS_OS)
  const char device[] = "COM3";
#elif defined(LINUX_OS)
  //const char device[] = "/dev/ttyUSB0";
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

  // Send "SCIP2.0" while changing the baud rate and output the response.
  long try_baudrate[] = { 115200, 19200, 38400 };
  size_t try_times = sizeof(try_baudrate)/sizeof(try_baudrate[0]);
  for (size_t i = 0; i < try_times; ++i) {

    // The baud rate on the host side is changed
    printf("set host baudrate: %ld\n", try_baudrate[i]);
    con.setBaudrate(try_baudrate[i]);
    con.flush();

    con.send("SCIP2.0\n", 8);

    // The response is output.
    enum { LineMax = 64 + 1, Timeout = 200 };
    char buffer[LineMax];
    int n;
    while ((n = readline(&con, buffer, LineMax, Timeout)) > 0) {
      printf("%s\n", buffer);
    }
  }

#if defined(WINDOWS_OS)
  printf("Hit return key.\n");
  getchar();
#endif

  return 0;
}

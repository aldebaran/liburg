/*!
  \example scip_20_cr.cpp

  \brief Execution sample of SS command

  \author Satofumi KAMIMURA

  $Id: scip_20_cr.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "SerialDevice.h"
#include "DetectOS.h"
#include "ConnectionUtils.h"
#include "ScipUtils.h"
#include <cstdio>

using namespace qrk;


//! main
int main(int argc, char *argv[])
{
  // Change the port name appropriately.
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

  // Call SCIP2.0 and neglect the response.
  enum { Timeout = 200 };
  con.send("SCIP2.0\n", 8);
  skip(&con, Timeout);

  // Change the rotation period and display the timestamp interval.
  int percent[] = { 10, 5, 0 };
  size_t try_times = sizeof(percent)/sizeof(percent[0]);
  for (size_t i = 0; i < try_times; ++i) {

    printf("CR: %d\n", percent[i]);
    char command[] = "CRxx\n";
    sprintf(command, "CR%02d\n", percent[i]);
    con.send(command, 5);
    int ret = recvReply(&con, Timeout);
    if ((ret != 0x00) && (ret != 0x0e) && (ret != 0x03)) {
      printf("CR: %d\n", ret);
#if defined(WINDOWS_OS)
      printf("Hit return key.\n");
      getchar();
#endif
      exit(1);
    }

    // Get 1 step data using MD. Use the 4th line which is a timestamp
    con.send("MD0000000101020\n", 16);
    // Wait for the data to return

    ret = recvReply(&con, Timeout);
    if (ret != 0x00) {
      printf("MD: %d\n", ret);
#if defined(WINDOWS_OS)
      printf("Hit return key.\n");
      getchar();
#endif
      exit(1);
    }

    int pre_timestamp = 0;
    for (int i = 0; i < 5; ++i) {
      // Display received data
      size_t line_count = 0;
      enum { LineMax = 64 + 1 };
      char buffer[LineMax];
      int n;
      while ((n = readline(&con, buffer, LineMax, Timeout)) > 0) {
        if (line_count == 2) {
          int timestamp = decode(buffer, 4);
          int diff = timestamp - pre_timestamp;
          if (diff < Timeout) {
            // If less than timeout, consider as normal and output the result.
            printf("%d [msec]\n", diff);
          }
          pre_timestamp = timestamp;
        }
        ++line_count;
      }
    }
  }

#if defined(WINDOWS_OS)
  printf("Hit return key.\n");
  getchar();
#endif

  return 0;
}

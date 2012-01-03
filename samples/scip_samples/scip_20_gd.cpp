/*!
  \example scip_20_gd.cpp

  \brief Get data using GD command

  \author Satofumi KAMIMURA

  $Id: scip_20_gd.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "DetectOS.h"
#include "SerialDevice.h"
#include "ConnectionUtils.h"
#include "ScipUtils.h"
#include <cstring>
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
  getchar();
#endif
    exit(1);
  }

  // Call SCIP2.0 and neglect the response.
  enum { Timeout = 200 };
  con.send("SCIP2.0\n", 8);
  skip(&con, Timeout);

  // Switch on URG's laser using BM command
  con.send("BM\n", 3);
  int ret = recvReply(&con, Timeout);
  if (ret < 0) {
    printf("BM fail: %d\n", ret);
#if defined(WINDOWS_OS)
  getchar();
#endif
    exit(1);
  }

  // Send GD command
  //
  // GD or GS
  // 0000  should be greater than AMIN value (AMIN: refer PP command)
  // 0725  should be less than AMAX value (AMAX: refer PP command)
  // 01    cluster value
  con.send("GD0000072501\n", 13);

  // Display received data
  enum {
    LineMax = 64 + 1 + 1,
    URG_04LX_MAX = 725,
    PacketByte = 3,
  };
  char buffer[LineMax];
  char data_buffer[(URG_04LX_MAX + 1) * PacketByte];
  int filled = 0;
  int line_count = 0;
  int n;
  while ((n = readline(&con, buffer, LineMax, Timeout)) > 0) {
    printf("%s\n", buffer);

    // Store data for decoding (All lines except first 3 are distance data)
    // line_count 0: Echo back
    //            1: Status
    //            2: Time stamp
    if (line_count >= 3) {
      int copy_size = n - 1;   // Last checksum is excluded
      memmove(&data_buffer[filled], buffer, copy_size);
      filled += copy_size;
    }
    ++line_count;
  }
  printf("\n");

  // Decode the received data
  // It is better to  decode line by line which results in good memory
  // management
  for (int i = 0; i < URG_04LX_MAX; ++i) {
    // Caution: Valid distance data should be within [DMIN,DMAX]
    int length = decode(&data_buffer[i * PacketByte], PacketByte);
    printf("%d, ", length);
    if ((i % 10) == 00) {
      printf("\n");
    }
  }
  printf("\n");

#if defined(WINDOWS_OS)
  printf("Hit return key.\n");
  getchar();
#endif

  return 0;
}

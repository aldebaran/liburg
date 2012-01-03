/*!
  \example scip_20_tm.cpp

  \brief Execution sample of "TMx" of SCIP2.0

  \author Satofumi KAMIMURA

  $Id: scip_20_tm.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "SerialDevice.h"
#include "ConnectionUtils.h"
#include "ScipUtils.h"
#include "DetectOS.h"
#include <cstdio>

using namespace qrk;


static long recvTm1Reply(Connection* con, int timeout)
{
  con->send("TM1\n", 4);

  // Read echo back and response
  int ret = recvReply(con, timeout);
  if (ret != 0x00) {
    fprintf(stderr, "recvReply: %d\n", ret);
    return -1;
  }

  // Read time stamp
  enum { TimestampLine = 5 + 1 };
  char buffer[TimestampLine];
  int n = readline(con, buffer, TimestampLine, timeout);
  long timestamp = 0;
  if (n == 5) {
    // Output timestamp
    printf("%s\n", buffer);

    // Decode time stamp
    timestamp = decode(buffer, 4);
  }

  // Read last line
  char recv_ch = '\0';
  n = con->receive(&recv_ch, 1, timeout);
  if (! isLF(recv_ch)) {
    return -2;
  }

  return timestamp;
}


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

  // Change to time stamp mode according to TM0
  con.send("TM0\n", 4);
  int ret = recvReply(&con, Timeout);
  if (ret != 0x00) {
    printf("%d: Please reboot URG.\n", ret);
#if defined(WINDOWS_OS)
    printf("Hit return key.\n");
    getchar();
#endif
    exit(1);
  }

  enum { TryTimes = 3 };
  for (int i = 0; i < TryTimes; ++i) {
    // Time stamp is acquired with TM1, then display
    long timestamp = recvTm1Reply(&con, Timeout);
    printf("=> %ld [msec]\n\n", timestamp);
  }

  // With TM2, come out of time stamp mode
  con.send("TM2\n", 4);
  ret = recvReply(&con, Timeout);
  if (ret != 0x00) {
    printf("%d: Please reboot URG.\n", ret);
#if defined(WINDOWS_OS)
    printf("Hit return key.\n");
    getchar();
#endif
    exit(1);
  }
  printf("exit normaly.\n");

#if defined(WINDOWS_OS)
  printf("Hit return key.\n");
  getchar();
#endif

  return 0;
}


/*!
  \example scip_20_scip.cpp

  \brief Execution sample of "SCIP2.0" of SCIP2.0

  \author Satofumi KAMIMURA

  $Id: scip_20_scip.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "SerialDevice.h"
#include "ScipUtils.h"
#include "DetectOS.h"
#include <cstdlib>
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

  // Call SCIP2.0 and display the response.
  enum { Timeout = 200, BufferMax = 64 + 1 };
  char buffer[BufferMax];

  for (int i = 0; i < 2; ++i) {
    con.send("SCIP2.0\n", 8);

    int n = con.receive(buffer, BufferMax, Timeout);
    for (int j = 0; j < n; ++j) {
      char ch = buffer[j];
      if (isprint(ch)) {
        printf("%c", ch);
      } else {
        printf("[%02x]\n", static_cast<unsigned char>(ch));
      }
    }
    printf("\n");
  }

#if defined(WINDOWS_OS)
  printf("Hit return key.\n");
  getchar();
#endif

  return 0;
}

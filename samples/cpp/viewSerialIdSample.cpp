/*!
  \example viewSerialIdSample.cpp

  \brief Displays serial ID of URG

  \author Satofumi KAMIMURA

  $Id: viewSerialIdSample.cpp 1683 2010-02-10 10:28:05Z satofumi $
*/

#include "UrgCtrl.h"
#include "UrgUtils.h"
#include <cstdio>

using namespace qrk;


//! main
int main(int argc, char *argv[])
{
#ifdef WINDOWS_OS
  const char device[] = "COM3";
#else
  const char device[] = "/dev/ttyACM0";
#endif

  UrgCtrl urg;
  if (! urg.connect(device)) {
    printf("UrgCtrl::connect: %s\n", urg.what());
    exit(1);
  }

  printf("Serial ID: %ld\n", urgSerialId<UrgCtrl>(&urg));

#ifdef MSC
  getchar();
#endif

  return 0;
}

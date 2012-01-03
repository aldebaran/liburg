/*!
  \example versionLines.cpp

  \brief Displays VV command data

  \author Satofumi KAMIMURA

  $Id: versionLines.cpp 1737 2010-03-06 07:15:19Z satofumi $
*/

#include "UrgDevice.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace qrk;
using namespace std;


//! main
int main(int argc, char *argv[])
{
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

  vector<string> lines;

  // Receive version information
  urg.versionLines(lines);
  if (lines.empty()) {
    cerr << "UrgDevice::versionLines: " << urg.what() << endl;
    exit(1);
  }

  // Display
  for (vector<string>::iterator it = lines.begin();
       it != lines.end(); ++it) {
    cout << *it << endl;
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

/*!
  \example viewVvSample.cpp

  \brief Displays VV command data

  \author Satofumi KAMIMURA

  $Id: viewVvSample.cpp 1683 2010-02-10 10:28:05Z satofumi $
*/

#include "UrgCtrl.h"
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

  UrgCtrl urg;
  if (! urg.connect(device)) {
    printf("UrgCtrl::connect: %s\n", urg.what());
    exit(1);
  }

  vector<string> lines;

  // Receive version information
  urg.versionLines(lines);
  if (lines.empty()) {
    cerr << "UrgCtrl::versionLines: " << urg.what() << endl;
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

/*!
  \example findUrgPortsSample.cpp

  \brief Sample of FindUrgPorts()

  \author Satofumi KAMIMURA

  $Id: findUrgPortsSample.cpp 1683 2010-02-10 10:28:05Z satofumi $
*/

#include "findUrgPorts.h"
#include <cstdio>

using namespace qrk;
using namespace std;


//! main
int main(int argc, char *argv[])
{
  vector<string> ports;
  findUrgPorts(ports);

  // Display all found ports
  printf("ports: %u\n", ports.size());
  for (vector<string>::iterator it = ports.begin();
       it != ports.end(); ++it) {
    printf("%s\n", it->c_str());
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

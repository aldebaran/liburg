/*!
  \example findUrgPorts.cpp

  \brief Sample to use FindUrgPorts function

  \author Satofumi KAMIMURA

  $Id: findUrgPorts.cpp 1737 2010-03-06 07:15:19Z satofumi $
*/

#include "findUrgPorts.h"
#include <SDL.h>

using namespace qrk;
using namespace std;


//! main
int main(int argc, char *argv[])
{
  vector<string> ports;
  findUrgPorts(ports);

  // display URG ports
  printf("ports: %u\n", ports.size());
  for (vector<string>::iterator it = ports.begin();
       it != ports.end(); ++it) {
    printf("%s\n", it->c_str());
  }

  return 0;
}

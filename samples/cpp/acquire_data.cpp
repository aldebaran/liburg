/*!
  \example acquire_data.cpp

  \brief Sample of acquisition sample of data

  \author Satofumi KAMIMURA

  $Id: acquire_data.cpp 1737 2010-03-06 07:15:19Z satofumi $
*/

#include "findUrgPorts.h"
#include "UrgDevice.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace qrk;
using namespace std;


namespace
{
  void outputCsv(ofstream& fout, const vector<long>& data)
  {
    for (vector<long>::const_iterator it = data.begin();
         it != data.end(); ++it) {
      // The distance data that are less than urg_minDistance() are shown
      // as invalide values
      fout << *it << ',';
    }
    fout << endl;
  }
}


//! main
int main(int argc, char *argv[])
{
  if (argc < 3) {
    cerr << "usage:" << endl
         << "\t" << argv[0] << " <number of scans> <output file>\n"
         << endl;
    exit(1);
  }
  int scan_times = atoi(argv[1]);
  max(scan_times, 0);
  ofstream fout(argv[2]);
  if (! fout.is_open()) {
    perror(argv[2]);
  }

  // Search URG port
  vector<string> ports;
  findUrgPorts(ports);

  if (ports.empty()) {
    cerr << "no ports." << endl;
    exit(1);
  }

  UrgDevice urg;
  if (! urg.connect(ports[0].c_str())) {
    cerr << "UrgDevice::connect: " << urg.what() << endl;
    exit(1);
  }

  // Get data by GD command
  vector<long> data;
  for (int i = 0; i < scan_times; ++i) {
    int n = urg.capture(data);
    if (n < 0) {
      continue;
    }
    outputCsv(fout, data);
    cout << (i + 1) << " scaned." << endl;
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

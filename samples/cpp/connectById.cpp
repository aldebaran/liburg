/*!
  \example connectById.cpp

  \brief Sample of connect to URG using by serial ID

  \author Satofumi KAMIMURA

  $Id: connectById.cpp 1683 2010-02-10 10:28:05Z satofumi $
*/

#include "UrgCtrl.h"
#include "UrgUtils.h"
#include "Connection.h"
#include "ConnectionUtils.h"
#include <iostream>

using namespace qrk;
using namespace std;


namespace
{
  bool adjustById(UrgCtrl urg[], long serials[], size_t n)
  {
    // Get serial ID
    vector<long> device_serials;
    for (size_t i = 0; i < n; ++i) {
      long serial_id = urgSerialId<UrgCtrl>(&urg[i]);
      device_serials.push_back(serial_id);
    }

    // Sort urg object
    for (size_t i = 0; i < n; ++i) {
      long requested_serial = serials[i];
      if (device_serials[i] == requested_serial) {
        continue;
      }

      vector<long>::iterator p =
        find(device_serials.begin(), device_serials.end(), requested_serial);
      if (p == device_serials.end()) {
        return false;
      }
      size_t swap_index = p - device_serials.begin();

      swapConnection<UrgCtrl>(urg[i], urg[swap_index]);
      swap(device_serials[i], device_serials[swap_index]);
    }

    return true;
  }
}


int main(int argc, char *argv[])
{
  // serial ID of URG that wants to connect
  long serials[] = {
    710002,
    614967,
  };
#ifdef WINDOWS_OS
  const char* devices[] = { "COM3", "COM4" };
#else
  const char* devices[] = { "/dev/ttyACM0", "/dev/ttyACM1" };
#endif

  UrgCtrl urg[2];

  // Connection
  size_t n = sizeof(serials) / sizeof(serials[0]);
  for (size_t i = 0; i < n; ++i) {
    if (! urg[i].connect(devices[i])) {
      cout << "UrgCtrl::connect: " << urg[i].what() << endl;
      exit(1);
    }
  }

  if (! adjustById(urg, serials, n)) {
    cout << "fail swapById()" << endl;
    exit(1);
  }

  // Display
  cout << "result" << endl;
  for (size_t i = 0; i < n; ++i) {
    cout << i << ", " << urgSerialId<UrgCtrl>(&urg[i]) << endl;
  }

  for (size_t i = 0; i < n; ++i) {
    delete urg[i].connection();
    urg[i].setConnection(NULL);
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

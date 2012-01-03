/*!
  \example captureIntensitySample.cpp

  \brief Sample to get intensity data

  \author Satofumi KAMIMURA

  $Id: captureIntensitySample.cpp 1845 2010-06-10 22:51:43Z satofumi $
*/

#include "UrgDevice.h"
#include "TcpipSocket.h"
#include "delay.h"
#include <SDL.h>
#include <cstdlib>

using namespace qrk;
using namespace std;


int main(int argc, char *argv[])
{
  const char address[] = "192.168.0.10";
  short port = 10940;

  UrgDevice urg;
  TcpipSocket tcpip;
  if (! tcpip.connect(address, port)) {
    printf("TcpipSocket::connect: %s\n", tcpip.what());
    exit(1);
  }

  urg.setConnection(&tcpip);
  urg.loadParameter();

  int scan_msec = urg.scanMsec();
  urg.setCaptureMode(IntensityCapture);
  urg.setCaptureRange(0, 760);

  enum {
    CaptureTimes = 10,
  };

  vector<long> data;
  vector<long> intensity_data;

  long previous_timestamp = 0;
  for (int i = 0; i < CaptureTimes; ++i) {
    fprintf(stderr, ".");

    long timestamp = 0;
    int data_n = urg.captureWithIntensity(data, intensity_data, &timestamp);
    if (data_n > 0) {
      int front_index = urg.rad2index(0.0);
#if 1
      printf("%d: %ld [mm] (%ld), %ld [msec] (%ld)\n",
             i, data[front_index], intensity_data[front_index], timestamp,
             timestamp - previous_timestamp);
#else
      (void)front_index;
      for (int j = 0; j < data_n; ++j) {
        printf("%ld(%ld), ", data[j], intensity_data[j]);
      }
      printf("\n");
#endif
      previous_timestamp = timestamp;
    } else {
      --i;
      delay(scan_msec);
    }
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

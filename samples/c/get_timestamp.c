/*!
  \example get_timestamp.c

  \brief Sample to get timestamp

  Get timestamp using TMO, TM1, TM2 command

  \author Satofumi KAMIMURA

  $Id: get_timestamp.c 1724 2010-02-25 10:43:11Z satofumi $
*/

#include "urg_ctrl.h"
#include <stdio.h>
#include <stdlib.h>


static void urg_exit(urg_t *urg, const char *message)
{
  printf("%s: %s\n", message, urg_error(urg));
  urg_disconnect(urg);

#ifdef MSC
  getchar();
#endif
  exit(1);
}


/*! main */
int main(int argc, char *argv[])
{
  enum {
    CaptureTimes = 10,
  };

#ifdef WINDOWS_OS
  const char device[] = "COM3"; /* For Windows */
#else
  const char device[] = "/dev/ttyACM0"; /* For Linux */
#endif

  long timestamp = 0;
  int ret = 0;
  int i;
  urg_t urg;

  /* Connection */
  urg_initialize(&urg);
  ret = urg_connect(&urg, device, 115200);
  if (ret < 0) {
    urg_exit(&urg, "urg_connect()");
  }

  /* Transit to timestamp mode and displays time stamp */
  urg_enableTimestampMode(&urg);
  for (i = 0; i < CaptureTimes; ++i) {
    timestamp = urg_currentTimestamp(&urg);
    printf("%02d: timestamp: %ld [msec]\n", i, timestamp);
  }
  urg_disableTimestampMode(&urg);

#ifdef MSC
  getchar();
#endif

  return 0;
}

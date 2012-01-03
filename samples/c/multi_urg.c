/*!
  \example multi_urg.c

  \brief Sample to get data from multiple URG.

  Display the front data of each URG, using 2 URG sensor.

  \author Satofumi KAMIMURA

  $Id: multi_urg.c 1724 2010-02-25 10:43:11Z satofumi $
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
    Times = 10,
    Urgs = 2,
  };

  urg_t urg[Urgs];
  long *data[Urgs];
  int data_max[Urgs];
  int timestamp;
  int ret;
  int n;
  int i;
  int k;

#ifdef WINDOWS_OS
  const char *devices[] = { "COM3", "COM4" }; /* For Windows */
#else
  const char *devices[] = { "/dev/ttyACM0", "/dev/ttyACM1" }; /* For Linux */
#endif

  /* Connection */
  for (i = 0; i < Urgs; ++i) {
    urg_initialize(&urg[i]);
    ret = urg_connect(&urg[i], devices[i], 115200);
    if (ret < 0) {
      urg_exit(&urg[i], "urg_connect()");
    }
    /* To clear existing MD command*/
    urg_laserOff(&urg[i]);

    /* It will become easy if some frames are skipped. */
    /* If specified skip is 2, then transferred data becomes half. */
    /* urg_setSkipLines(&urg[i], 2); */

    /* Reserve for receive buffer */
    data_max[i] = urg_dataMax(&urg[i]);
    data[i] = (long*)malloc(sizeof(long) * data_max[i]);
    if (data[i] == NULL) {
      perror("data buffer");
      exit(1);
    }
  }

  /* Request for MD data */
  for (i = 0; i < Urgs; ++i) {
    urg_setCaptureTimes(&urg[i], Times);

    /* Request for data */
    ret = urg_requestData(&urg[i], URG_MD, URG_FIRST, URG_LAST);
    if (ret < 0) {
      urg_exit(&urg[i], "urg_requestData()");
    }
  }

  for (k = 0; k < Times; ++k) {
    for (i = 0; i < Urgs; ++i) {
      /* Ends when data reception is completed */
      int remain_times = urg_remainCaptureTimes(&urg[i]);
      printf("    %d: ", i);
      printf("(%03d/%03d): ", remain_times, Times);
      if (remain_times <= 0) {
        printf("\n");
        continue;
      }

      /* Reception */
      n = urg_receiveData(&urg[i], data[i], data_max[i]);
      if (n < 0) {
        /* Continue processing, because there is chances of receiving the
           data next time. */
        printf("%s: %s\n", "urg_receiveData()", urg_error(urg));

      } else {

        /* Display */
        timestamp = urg_recentTimestamp(&urg[i]);
        printf("timestamp: %d, ", timestamp);
#if 0
        {
          int j;
          for (j = 0; j < n; ++j) {
            /* Neglect if distance data is less than urg_minDistance() */
            printf("%d:%ld, ", j, data[i][j]);
          }
          printf("\n");
        }
#endif
        printf("\n");
      }
    }
  }

  /* Disconnect */
  for (i = 0; i < Urgs; ++i) {
    urg_disconnect(&urg[i]);
    free(data[i]);
  }

#ifdef MSC
  getchar();
#endif

  return 0;
}

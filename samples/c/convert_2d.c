/*!
  \example convert_2d.c

  \brief Sample of 2D representation of URG data

  \author Satofumi KAMIMURA

  $Id: convert_2d.c 1733 2010-03-06 01:19:49Z satofumi $
*/

#include <math.h>
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
#ifdef WINDOWS_OS
  const char device[] = "COM3"; /* For Windows */
#else
  const char device[] = "/dev/ttyACM0"; /* For Linux */
#endif

  long *data = NULL;
  int data_max;
  int min_length = 0;
  int max_length = 0;
  int ret;
  int n;
  int i;

  /* Connection */
  urg_t urg;
  urg_initialize(&urg);
  ret = urg_connect(&urg, device, 115200);
  if (ret < 0) {
    urg_exit(&urg, "urg_connect()");
  }

  /* Reserve for Reception data */
  data_max = urg_dataMax(&urg);
  data = (long*)malloc(sizeof(long) * data_max);
  if (data == NULL) {
    perror("data buffer");
    exit(1);
  }

  /* Request for GD data */
  ret = urg_requestData(&urg, URG_GD, URG_FIRST, URG_LAST);
  if (ret < 0) {
    urg_exit(&urg, "urg_requestData()");
  }

  /* Reception */
  n = urg_receiveData(&urg, data, data_max);
  if (n < 0) {
    urg_exit(&urg, "urg_receiveData()");
  }

  /* Output as 2 dimensional data */
  /* Consider front of URG as positive direction of X axis */
  min_length = urg_minDistance(&urg);
  max_length = urg_maxDistance(&urg);
  for (i = 0; i < n; ++i) {
    int x, y;
    long length = data[i];

    /* Neglect the out of range values */
    if ((length <= min_length) || (length >= max_length)) {
      continue;
    }

    x = (int)(length * cos(urg_index2rad(&urg, i)));
    y = (int)(length * sin(urg_index2rad(&urg, i)));

    printf("%d\t%d\t# %d, %ld\n", x, y, i, length);
  }

  urg_disconnect(&urg);
  free(data);

#ifdef MSC
  getchar();
#endif

  return 0;
}

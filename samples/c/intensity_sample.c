/*!
  \example intensity_sample.c

  \brief Sample of intensity scan

  \author Satofumi KAMIMURA

  $Id: intensity_sample.c 1950 2011-05-07 08:18:39Z satofumi $
*/

#include "urg_ctrl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


static void urg_exit(urg_t *urg, const char *message)
{
  printf("%s: %s\n", message, urg_error(urg));
  urg_disconnect(urg);

#ifdef MSC
  getchar();
#endif
  exit(1);
}


static void printData(urg_t *urg, urg_parameter_t *parameter,
                      long data[], int data_size, long intensity[])
{
#if 1
  int timestamp = urg_recentTimestamp(urg);

  /* Display the front data with timestamp */
  /* Neglect the distance data if it is less than urg_minDistance() */
  printf("%d: %ld [mm] (%ld) %d [msec]\n", parameter->area_front_,
         data[parameter->area_front_],
         intensity[parameter->area_front_],
         timestamp);
#else
  /* Display the all data */
  int i;

  for (i = 0; i < data_size; ++i) {
    printf("%d: %ld [mm] (%ld)\n", i, data[i], intensity[i]);
  }
#endif
}


/*! main */
int main(int argc, char *argv[])
{
  enum {
    CaptureTimes = 1,
  };

#ifdef WINDOWS_OS
  const char device[] = "COM3"; /* For Windows */
#else
  const char device[] = "/dev/ttyACM0"; /* For Linux */
#endif

  int data_max;
  long* data;
  long* intensity;
  //int scan_msec;
  urg_parameter_t parameter;
  int ret;
  int n;
  int i;
  urg_t urg;

  /* Connection */
  urg_initialize(&urg);
  ret = urg_connect(&urg, device, 115200);
  if (ret < 0) {
    urg_exit(&urg, "urg_connect()");
  }

  /* Reserve for receive buffer */
  data_max = urg_dataMax(&urg);
  data = (long*)malloc(sizeof(long) * data_max);
  if (data == NULL) {
    perror("data buffer");
    exit(1);
  }
  intensity = (long*)malloc(sizeof(long) * data_max);
  if (intensity == NULL) {
    perror("data buffer");
    exit(1);
  }

  urg_parameters(&urg, &parameter);
  //scan_msec = urg_scanMsec(&urg);

  if (strcmp("UTM-30LX", urg_model(&urg))) {
    /* Top-URG is excluded */

    /* Request for Data using GD */
    printf("GD capture\n");
    for (i = 0; i < CaptureTimes; ++i) {
      /* Request for GD intensity data */
      ret = urg_requestData(&urg, URG_GD_INTENSITY, URG_FIRST, URG_LAST);
      if (ret < 0) {
        urg_exit(&urg, "urg_requestData()");
      }

    /* Reception */
      n = urg_receiveDataWithIntensity(&urg, data, data_max, intensity);
      if (n < 0) {
        urg_exit(&urg, "urg_receiveData()");
      }
      printData(&urg, &parameter, data, n, intensity);
    }
    printf("\n");
  }

  /* Request for Data using MD */
  printf("MD(ME) capture\n");

  /* set data acquisition frequency equal to infinity, to get the data more
     than 100 times */
  /* urg_setCaptureTimes(&urg, UrgInfinityTimes); */
  assert(CaptureTimes < 100);
  urg_setCaptureTimes(&urg, CaptureTimes);

  /* Request for data */
  ret = urg_requestData(&urg, URG_MD_INTENSITY, URG_FIRST, URG_LAST);
  if (ret < 0) {
    urg_exit(&urg, "urg_requestData()");
  }

  for (i = 0; i < CaptureTimes; ++i) {
    /* Reception */
    n = urg_receiveDataWithIntensity(&urg, data, data_max, intensity);
    if (n < 0) {
      urg_exit(&urg, "urg_receiveData()");
    }
    printData(&urg, &parameter, data, n, intensity);
  }

  urg_disconnect(&urg);
  free(data);
  free(intensity);

#ifdef MSC
  getchar();
#endif

  return 0;
}

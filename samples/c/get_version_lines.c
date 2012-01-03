/*!
  \example get_version_lines.c

  \brief Get version information

  Get URG's Version string

  \author Satofumi KAMIMURA

  $Id: get_version_lines.c 1724 2010-02-25 10:43:11Z satofumi $
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
    LinesMax = 5,
  };

#ifdef WINDOWS_OS
  const char device[] = "COM4"; /* For Windows */
#else
  const char device[] = "/dev/ttyACM0"; /* For Linux */
#endif

  char buffer[LinesMax][UrgLineWidth];
  char *lines[LinesMax];
  int ret;
  int i;
  urg_t urg;

  /* Connection */
  urg_initialize(&urg);
  ret = urg_connect(&urg, device, 115200);
  if (ret < 0) {
    urg_exit(&urg, "urg_connect()");
  }

  /* Get version information */
  for (i = 0; i < LinesMax; ++i) {
    lines[i] = buffer[i];
  }
  ret = urg_versionLines(&urg, lines, LinesMax);
  printf("urg_getVersion: %s\n", urg_error(&urg));
  if (ret < 0) {
    urg_disconnect(&urg);
    exit(1);
  }

  /* Display */
  for (i = 0; i < LinesMax; ++i) {
    printf("%s\n", lines[i]);
  }

  /* Disconnect */
  urg_disconnect(&urg);

#ifdef MSC
  getchar();
#endif

  return 0;
}

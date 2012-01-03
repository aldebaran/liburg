/*!
  \file
  \brief ë“ã@ä÷êî

  \author Satofumi KAMIMURA

  $Id: delay.c 1374 2009-10-07 00:05:06Z satofumi $
*/

#include "detect_os.h"
#if defined(WINDOWS_OS)
#include <windows.h>
#include <time.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

#if defined(MSC)
#pragma comment(lib, "winmm.lib")
#endif

enum {
  False = 0,
  True,
};

#if defined(WINDOWS_OS)
static int is_initialized_ = False;
#endif


void delay(int msec)
{
#if defined(WINDOWS_OS)
  if (is_initialized_ == False) {
    timeBeginPeriod(1);
    is_initialized_ = True;
  }
  Sleep(msec);

#else
  // !!! Mac Ç≈ìÆçÏÇµÇ»Ç¢ÇÊÇ§Ç»ÇÁÇŒÅAí≤êÆÇ∑ÇÈ
  usleep(1000 * msec);
#endif
}

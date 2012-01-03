/*!
  \file
  \brief ���O�̋L�^�֐�

  \author Satofumi KAMIMURA

  $Id: log_printf.cpp 772 2009-05-05 06:57:57Z satofumi $
*/

#include "log_printf.h"
#include <cstdio>
#include <cstdarg>


namespace
{
  const char* LogFile = "error_log.txt";
}


int qrk::log_printf(const char *format, ...)
{
  static FILE* fd = NULL;
  if (fd == NULL) {
    fd = fopen(LogFile, "w");
    if (fd == NULL) {
      return -1;
    }
  }

  va_list ap;

  // �W���G���[�o��
  va_start(ap, format);
  vfprintf(stderr, format, ap);
  va_end(ap);

  // �t�@�C���o��
  va_start(ap, format);
  int ret = vfprintf(fd, format, ap);
  va_end(ap);

  // fclose() ����@��Ȃ��̂ŁA���e�������o���Ă���
  fflush(fd);

  return ret;
}

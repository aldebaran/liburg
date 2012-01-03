#ifndef QRK_DETECT_OS_H
#define QRK_DETECT_OS_H

/*!
  \file
  \brief ����OS�̌��o

  \author Satofumi KAMIMURA

  $Id: DetectOS.h 1498 2009-11-05 15:28:42Z satofumi $
*/

#if defined _MSC_VER || defined __CYGWIN__ || defined __MINGW32__
#define WINDOWS_OS

#if defined _MSC_VER
#define MSC
#elif defined __CYGWIN__
#define Cygwin
#elif defined __MINGW32__
#define MinGW
#endif

#elif defined __linux__
#define LINUX_OS

#else
// ���o�ł��Ȃ��Ƃ����AMac �����ɂ��Ă��܂�
#define MAC_OS
#endif

#endif /* !QRK_DETECT_OS_H */

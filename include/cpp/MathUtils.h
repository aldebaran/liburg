#ifndef QRK_MATH_UTILS_H
#define QRK_MATH_UTILS_H

/*!
  \file
  \brief 数学関数の補助ファイル

  \author Satofumi KAMIMURA

  $Id: MathUtils.h 1545 2009-11-22 10:03:00Z satofumi $
*/

#include "DetectOS.h"
#if defined(WINDOWS_OS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifndef M_PI
// Visual C++ 6.0 用
#define M_PI 3.14159265358979323846 //!< 円周率
#endif

#if defined(MSC)
extern long lrint(double x);
#endif

#endif /* !QRK_MATH_UTILS_H */

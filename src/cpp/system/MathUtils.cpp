/*!
  \file
  \brief 数学関数の補助ファイル

  \author Satofumi KAMIMURA

  $Id: MathUtils.cpp 1545 2009-11-22 10:03:00Z satofumi $
*/

#include "MathUtils.h"

#if defined(MSC)
long lrint(double x)
{
  if (x >= 0) {
    x += 0.5;
  } else {
    x -= 0.5;
  }
  return static_cast<long>(x);
}
#endif

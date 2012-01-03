#ifndef QRK_POINT_H
#define QRK_POINT_H

/*!
  \file
  \brief ˆÊ’u‚ÌŒ^’è‹`

  \author Satofumi KAMIMURA

  $Id: Point.h 1283 2009-09-09 22:14:18Z satofumi $
*/

namespace qrk
{
  /*!
    \brief ˆÊ’u‚ÌŒ^’è‹`
  */
  template <typename T>
  class Point
  {
  public:
    T x;
    T y;


    Point(void) : x(0), y(0)
    {
    }


    Point(T x_, T y_) : x(x_), y(y_)
    {
    }


    bool operator == (const Point<T>& rhs) const
    {
      return ((this->x == rhs.x) && (this->y == rhs.y)) ? true : false;
    }


    bool operator < (const Point<T>& rhs) const
    {
      if (y < rhs.y) {
        return true;

      } else if (x < rhs.x) {
        return true;

      } else {
        return false;
      }
    }


    Point<T>& operator += (const Point<T>& rhs)
    {
      this->x += rhs.x;
      this->y += rhs.y;

      return *this;
    }


    const Point<T> operator + (const Point<T>& rhs) const
    {
      return Point<T>(*this) += rhs;
    }


    Point<T>& operator -= (const Point<T>& rhs)
    {
      this->x -= rhs.x;
      this->y -= rhs.y;

      return *this;
    }


    const Point<T> operator - (const Point<T>& rhs) const
    {
      return Point<T>(*this) -= rhs;
    }
  };
}

#endif /* !QRK_POINT_H */

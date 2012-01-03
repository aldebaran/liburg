#ifndef QRK_TICKS_H
#define QRK_TICKS_H

/*!
  \file
  \brief タイムスタンプ取得関数

  \author Satofumi KAMIMURA

  $Id: ticks.h 1402 2009-10-11 12:45:16Z satofumi $
*/


//! Quick Robot Development Kit
namespace qrk
{
  /*!
    \brief タイムスタンプの取得

    \retval タイムスタンプ [msec]
  */
  extern int ticks(void);
}

#endif /* !QRK_TICKS_H */

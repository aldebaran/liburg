#ifndef QRK_LOG_PRINTF_H
#define QRK_LOG_PRINTF_H

/*!
  \file
  \brief ログの記録関数

  \author Satofumi KAMIMURA

  $Id: log_printf.h 772 2009-05-05 06:57:57Z satofumi $
*/

namespace qrk
{
  /*!
    \brief ログ記録用

    \param[in] format 可変引数
  */
  int log_printf(const char *format, ...);


  /*!
    \brief 出力ファイル名を変更する

    \attention 最初に log_printf() が呼ばれる前に呼び出されなければならない
  */
  void log_setName(const char* file_name);
}

#endif /* !QRK_LOG_PRINTF_H */

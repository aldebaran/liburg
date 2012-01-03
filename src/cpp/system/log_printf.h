#ifndef QRK_LOG_PRINTF_H
#define QRK_LOG_PRINTF_H

/*!
  \file
  \brief ���O�̋L�^�֐�

  \author Satofumi KAMIMURA

  $Id: log_printf.h 772 2009-05-05 06:57:57Z satofumi $
*/

namespace qrk
{
  /*!
    \brief ���O�L�^�p

    \param[in] format �ψ���
  */
  int log_printf(const char *format, ...);


  /*!
    \brief �o�̓t�@�C������ύX����

    \attention �ŏ��� log_printf() ���Ă΂��O�ɌĂяo����Ȃ���΂Ȃ�Ȃ�
  */
  void log_setName(const char* file_name);
}

#endif /* !QRK_LOG_PRINTF_H */

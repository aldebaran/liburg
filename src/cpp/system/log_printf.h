#ifndef QRK_LOG_PRINTF_H
#define QRK_LOG_PRINTF_H

/*!
  \file
  \brief ���O�̋L�^�֐�

  \author Satofumi KAMIMURA

  $Id: log_printf.h 1811 2010-04-30 16:12:05Z satofumi $
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

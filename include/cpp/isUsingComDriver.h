#ifndef QRK_IS_USING_COM_DRIVER_H
#define QRK_IS_USING_COM_DRIVER_H

/*!
  \file
  \brief �w��h���C�o�����p�����𔻒f����

  \author Satofumi KAMIMURA

  $Id: isUsingComDriver.h 783 2009-05-05 08:56:26Z satofumi $
*/

namespace qrk
{
  /*!
    \brief �w��h���C�o�𗘗p���Ă��� COM �|�[�g�����݂��邩��Ԃ�

    \param[in] com_port ������s�� COM �|�[�g
    \param[in] driver_name ������s���h���C�o��

    \retval true �w��h���C�o�� COM �|�[�g�����݂���
    \retval false ���݂��Ȃ�

    \attention Windows ���łȂ���Ώ�� false ��Ԃ�
    \attention ����m�F�́AWindows XP �̂݁B���ł͖�����
  */
  bool isUsingComDriver(const char* com_port, const char* driver_name);
}

#endif /* !QRK_IS_USING_COM_DRIVER_H */

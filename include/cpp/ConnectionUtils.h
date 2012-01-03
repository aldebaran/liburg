#ifndef QRK_CONNECTION_UTILS_H
#define QRK_CONNECTION_UTILS_H

/*!
  \file
  \brief Connection ��p�����⏕�֐�

  \author Satofumi KAMIMURA

  $Id: ConnectionUtils.h 1838 2010-06-01 03:17:17Z satofumi $
*/

#include <cstddef>
#include <algorithm>


//! Quick Robot Develoment Kit.
namespace qrk
{
    class Connection;


    /*!
      \brief ���s�R�[�h����Ԃ�

      \retval true LF, CR �̂Ƃ�
      \retval false ��L�ȊO�̂Ƃ�
    */
    extern bool isLF(const char ch);


    /*!
      \brief ��M�f�[�^��ǂݔ�΂�

      Connection::clear() �Ƃ́A�^�C���A�E�g���Ԃ��w�肵�ēǂݔ�΂���_���قȂ�

      \param[in,out] con �ʐM���\�[�X
      \param[in] total_timeout �^�C���A�E�g���Ԃ̏�� [msec]
      \param[in] each_timeout ��M�f�[�^�Ԃɂ�����^�C���A�E�g���Ԃ̏�� [msec]
    */
    extern void skip(Connection* con, int total_timeout, int each_timeout = 0);


    /*!
      \brief ���s�܂ł̃f�[�^�ǂݏo��

      ������I�[�� \\0 ��t�����ĕԂ�

      \param[in,out] con �ʐM���\�[�X
      \param[out] buf ��M�o�b�t�@
      \param[in] count ��M�o�b�t�@�̍ő�T�C�Y
      \param[in] timeout �^�C���A�E�g [msec]

      \return ��M������ (��M���Ȃ��ă^�C���A�E�g�����ꍇ�� -1)
    */
    extern int readline(Connection* con, char* buf, const size_t count,
                        int timeout);


    /*!
      \brief �ڑ��I�u�W�F�N�g�̌���

      a �� b �̐ڑ��I�u�W�F�N�g����������B
    */
    template <class T>
    void swapConnection(T& a, T& b)
    {
        Connection* t = a.connection();
        a.setConnection(b.connection());
        b.setConnection(t);
    }
}

#endif /* !QRK_CONNECTION_UTILS_H */

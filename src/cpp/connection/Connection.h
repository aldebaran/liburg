#ifndef QRK_CONNECTION_H
#define QRK_CONNECTION_H

/*!
  \file
  \brief �ʐM�C���^�[�t�F�[�X

  \author Satofumi KAMIMURA

  $Id: Connection.h 1811 2010-04-30 16:12:05Z satofumi $
*/

#include <cstddef>


namespace qrk
{
    enum {
        ReceiveTimeout = -1,
        ErrorLastIndex = -2,
    };


    //! �ʐM�C���^�[�t�F�[�X
    class Connection
    {
    public:
        virtual ~Connection(void) {}


        /*!
          \brief ������Ԃ�Ԃ�

          \return ������Ԃ�����������
        */
        virtual const char* what(void) const = 0;


        /*!
          \brief �f�o�C�X�ւ̐ڑ�

          \param[in] device �ڑ��f�o�C�X��
          \param[in] baudrate �ڑ��{�[���[�g

          \retval true ����
          \retval false ���s
        */
        virtual bool connect(const char* device, long baudrate) = 0;


        /*!
          \brief �ؒf
        */
        virtual void disconnect(void) = 0;


        /*!
          \brief �{�[���[�g�̕ύX

          \param[in] baudrate �{�[���[�g

          \retval 0 ����
          \retval < 0 �G���[
        */
        virtual bool setBaudrate(long baudrate) = 0;


        /*!
          \brief �{�[���[�g��Ԃ�

          \retval �{�[���[�g

          \attention SerialDevice �ł̂ݗL��
        */
        virtual long baudrate(void) const = 0;


        /*!
          \brief �ڑ���Ԃ�Ԃ�

          \retval true �ڑ���
          \retval false �ؒf��
        */
        virtual bool isConnected(void) const = 0;


        /*!
          \brief ���M

          \param[in] data ���M�f�[�^
          \param[in] count ���M�o�C�g��

          \return ���M�����o�C�g��
        */
        virtual int send(const char* data, size_t count) = 0;


        /*!
          \brief ��M

          \param[out] data ��M�p�o�b�t�@
          \param[in] count ��M�o�b�t�@�̍ő�T�C�Y
          \param[in] timeout �^�C���A�E�g���� [msec]
        */
        virtual int receive(char* data, size_t count, int timeout) = 0;


        /*!
          \brief ��M�ς݃f�[�^�̃o�C�g����Ԃ�

          \return ��M�ς݃f�[�^�̃o�C�g��
        */
        virtual size_t size(void) const = 0;


        /*!
          \brief �o�b�t�@�̓��e�������I�ɏo�͂���
        */
        virtual void flush(void) = 0;


        /*!
          \brief ����M�f�[�^�̃N���A

          ���M�o�b�t�@�A��M�ς݃f�[�^���N���A����
        */
        virtual void clear(void) = 0;


        /*!
          \brief �P���������߂�

          \param[in] ch �����߂�����
        */
        virtual void ungetc(const char ch) = 0;
    };
}

#endif /* !QRK_CONNECTION_H */

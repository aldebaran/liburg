#ifndef QRK_TCPIP_SOCKET_H
#define QRK_TCPIP_SOCKET_H

/*!
  \file
  \brief TCP/IP �ʐM

  \author Satofumi KAMIMURA

  $Id: TcpipSocket.h 1817 2010-05-09 09:04:32Z satofumi $
*/

#include "Connection.h"
#include <string>
#include <memory>


namespace qrk
{
    class SocketSet;


    //! TCP/IP �ʐM
    class TcpipSocket : public Connection
    {
    public:
        TcpipSocket(void);


        /*!
          \brief �R���X�g���N�^

          \param[in] socket �ʐM�\�P�b�g
        */
        TcpipSocket(void* socket);


        /*!
          \brief �R���X�g���N�^

          \param[in] socket_set �ʐM�\�P�b�g�Ǘ�
          \param[in] socket �ʐM�\�P�b�g
        */
        TcpipSocket(SocketSet* socket_set, void* socket = NULL);

        ~TcpipSocket(void);

        const char* what(void) const;

        bool connect(const char* host, long port);
        void disconnect(void);
        bool setBaudrate(long baudrate);
        long baudrate(void) const;
        bool isConnected(void) const;
        int send(const char* data, size_t count);
        int receive(char* data, size_t count, int timeout);
        size_t size(void) const;
        void flush(void);
        void clear(void);
        void ungetc(const char ch);

    private:
        TcpipSocket(const TcpipSocket& rhs);
        TcpipSocket& operator = (const TcpipSocket& rhs);

        struct pImpl;
        const std::auto_ptr<pImpl> pimpl;
    };
}

#endif /* !QRK_TCPIP_SOCKET_H */

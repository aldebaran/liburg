#ifndef QRK_DEVICE_SERVER_H
#define QRK_DEVICE_SERVER_H

/*!
  \file
  \brief �V�~�����[�V�����p�̃f�o�C�X�T�[�o

  \author Satofumi KAMIMURA

  $Id: DeviceServer.h 783 2009-05-05 08:56:26Z satofumi $
*/

namespace qrk
{
  /*!
    \brief �V�~�����[�V�����p�̃f�o�C�X�T�[�o
  */
  class DeviceServer
  {
  public:
    virtual ~DeviceServer(void)
    {
    }

    virtual bool activate(long port) = 0;

    virtual int updateInterval(void) = 0;

    virtual void update(void) = 0;
  };
}

#endif /* !QRK_DEVICE_SERVER_H */

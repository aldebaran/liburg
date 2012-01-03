#ifndef QRK_IS_USB_COM_H
#define QRK_IS_USB_COM_H

/*!
  \file
  \brief USB �|�[�g���ǂ����𔻕ʂ���

  \author Satofumi KAMIMURA

  $Id: IsUsbCom.h 1811 2010-04-30 16:12:05Z satofumi $
*/

#include <vector>
#include <string>


namespace qrk
{
    //! USB �|�[�g�̔��ʃN���X
    class IsUsbCom {
    public:
        virtual ~IsUsbCom(void) {
        }


        /*!
          \brief �o�^�ς݂̃|�[�g�̃x�[�X����Ԃ�

          Linux �����ŗp����

          \return �|�[�g�̃x�[�X��
        */
        virtual std::vector<std::string> baseNames(void) const
        {
            std::vector<std::string> dummy;
            return dummy;
        }


        /*!
          \brief �D��\������h���C�o����Ԃ�

          Windows �����ŗp����

          \return �h���C�o��
        */
        virtual std::vector<std::string> usbDrivers(void) const
        {
            std::vector<std::string> dummy;
            return dummy;
        }
    };
}

#endif /* !QRK_IS_USB_COM_H */

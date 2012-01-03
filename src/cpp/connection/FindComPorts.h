#ifndef QRK_FIND_COM_PORTS_H
#define QRK_FIND_COM_PORTS_H

/*!
  \file
  \brief COM �|�[�g�ꗗ�̎擾

  \author Satofumi KAMIMURA

  $Id: FindComPorts.h 1811 2010-04-30 16:12:05Z satofumi $

  \attention ����m�F�� Windows XP �̂݁B���ł͖�����
*/

#include <string>
#include <vector>
#include <memory>


namespace qrk
{
    /*!
      \brief �V���A���|�[�g�̒T�����s��

      Windows �ł́A���W�X�g���������� COM �ꗗ���擾���ĕԂ��B\n
      Linux, MacOS �ł́A�^����ꂽ�p�^�[���Ɉ�v����t�@�C�������擾���ĕԂ��B
    */
    class FindComPorts
    {
    public:
        FindComPorts(void);
        ~FindComPorts(void);


        /*!
          \brief �o�^�ς݂̃x�[�X���̃N���A
        */
        void clearBaseNames(void);


        /*!
          \brief �T���ŗp����|�[�g�̃x�[�X����ǉ�����

          \param[in] base_name �|�[�g�̃x�[�X��
        */
        void addBaseName(const char* base_name);


        /*!
          \brief �o�^�ς݂̃|�[�g�̃x�[�X����Ԃ�

          Linux �����ŗp����

          \return �|�[�g�̃x�[�X��
        */
        std::vector<std::string> baseNames(void);


        void addDriverName(const char* driver_name);


        /*!
          \brief COM �|�[�g�ꗗ�̎擾

          \param[out] ports ���o�����|�[�g
          \param[in] all_ports addDriverName() �Ŏw�肵���|�[�g�̂ݎ擾����Ƃ� false

          \retval COM �ꗗ���i�[���ꂽ string �z��
        */
        size_t find(std::vector<std::string>& ports, bool all_ports = true);

        size_t find(std::vector<std::string>& ports,
                    std::vector<std::string>& driver_names, bool all_ports = true);

    private:
        FindComPorts(const FindComPorts& rhs);
        FindComPorts& operator = (const FindComPorts& rhs);

        struct pImpl;
        std::auto_ptr<pImpl> pimpl;
    };
}

#endif /* !QRK_FIND_COM_PORTS_H */

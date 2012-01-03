#ifndef QRK_FIND_FILES_H
#define QRK_FIND_FILES_H

/*!
  \file
  \brief �f�B���N�g���ȉ��̃t�@�C���T�����s��

  \author Satofumi KAMIMURA

  $Id: findFiles.h 1663 2010-02-01 07:17:58Z satofumi $
*/

#include <boost/xpressive/xpressive.hpp>
#include <vector>
#include <string>


namespace qrk
{
  /*!
    �f�B���N�g���ȉ��̃t�@�C���T�����s��

    \param[out] files ���t�������t�@�C��
    \param[in] root_path �T���̃��[�g�f�B���N�g��
    \param[in] pattern �t�@�C���̌����p�^�[��

    \return ���t�������t�@�C����
  */
  extern size_t findFiles(std::vector<std::string>& files,
                          const char* root_path,
                          const boost::xpressive::sregex pattern);
}

#endif /* !QRK_FIND_FILES_H */

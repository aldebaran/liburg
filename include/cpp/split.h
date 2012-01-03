#ifndef QRK_SPLIT_H
#define QRK_SPLIT_H

/*!
  \file
  \brief string �p�� split �֐�

  \author Satofumi KAMIMURA

  $Id: split.h 1811 2010-04-30 16:12:05Z satofumi $
*/

#include <vector>
#include <string>


namespace qrk
{
    /*!
      \brief �w�蕶���ɂ�镪��

      \param[out] tokens ������̕�����
      \param[in] original �����Ώۂ̕�����
      \param[in] split_pattern �������s�������̗�
      \param[in] continious_pattern �A�������Z�p���[�^���P�̃Z�p���[�^�Ƃ��Ĉ���

      \return ������̃g�[�N����
    */
    size_t split(std::vector<std::string>& tokens,
                 const std::string& original, const char* split_pattern = " \t",
                 bool continious_pattern = true);
}

#endif /* !QRK_SPLIT_H */

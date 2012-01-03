#ifndef QRK_SEMAPHORE_H
#define QRK_SEMAPHORE_H

/*!
  \file
  \brief �Z�}�t�H�Ǘ�

  \author Satofumi KAMIMURA

  $Id: Semaphore.h 1949 2011-05-06 07:18:01Z satofumi $

  �h�L�������g�́ASDL �}�j���A�����Q�l�ɂ��Ă���
*/

#include <memory>
#include <cstddef>


namespace qrk
{
  /*!
    \brief �Z�}�t�H�Ǘ�
  */
  class Semaphore
  {
    Semaphore(void);
    Semaphore(const Semaphore& rhs);
    Semaphore& operator = (const Semaphore& rhs);

    struct pImpl;
    const std::auto_ptr<pImpl> pimpl;

  public:
    /*!
      \brief �R���X�g���N�^

      \param[in] initial_value �����l
    */
    explicit Semaphore(size_t initial_value);
    ~Semaphore(void);


    /*!
      \brief �f�N�������g

      �Z�}�t�H�����b�N���A�Z�}�t�H�̒l���[���̂Ƃ��́A�X���b�h���~������
    */
    void wait(void);


    /*!
      \brief �X���b�h����~���Ȃ��f�N�������g

      �X���b�h���~�������ɁA�Z�}�t�H�̃��b�N�����݂�

      \retval true ���b�N�ɐ���
      \retval false ���b�N�Ɏ��s or �G���[
    */
    bool tryWait(void);


    /*!
      \brief �C���N�������g

      �Z�}�t�H�̒l�����Z����
    */
    void post(void);


    /*!
      \brief �Z�}�t�H�l�̎擾

      \return �Z�}�t�H�l
    */
    size_t value(void);
  };
}

#endif /*! QRK_SEMAPHORE_H */

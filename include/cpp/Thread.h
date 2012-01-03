#ifndef QRK_THREAD_H
#define QRK_THREAD_H

/*!
  \file
  \brief �X���b�h�����̃��b�p�[

  \author Satofumi KAMIMURA

  $Id: Thread.h 914 2009-05-20 22:16:35Z satofumi $
*/

#include <memory>


namespace qrk
{
  /*!
    \brief �X���b�h����
  */
  class Thread
  {
    Thread(void);
    Thread(const Thread& rhs);
    Thread& operator = (const Thread& rhs);

    struct pImpl;
    const std::auto_ptr<pImpl> pimpl;

  public:
    enum {
      Infinity = -1,
    };

    /*!
      \brief �R���X�g���N�^

      \param[in,out] fn �֐��|�C���^
      \param[in,out] args �X���b�h�֐��ւ̈���
    */
    explicit Thread(int (*fn)(void *), void* args);
    ~Thread(void);


    /*!
      \brief �����񐔂��w�肵�ăX���b�h���N��

      \param[in] times ������
    */
    void run(int times = 1);


    /*!
      \brief �X���b�h���~
    */
    void stop(void);


    /*!
      \brief �X���b�h�̏I����҂�

      \return �X���b�h�̖߂�l
    */
    int wait(void);


    /*!
      \brief �X���b�h�����쒆����Ԃ�

      \retval true ���쒆
      \retval false ��~��
    */
    bool isRunning(void) const;
  };
}

#endif /* !QRK_THREAD_H */

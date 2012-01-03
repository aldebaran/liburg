#ifndef QRK_LOCK_GUARD_H
#define QRK_LOCK_GUARD_H

/*!
  \file
  \brief ���b�N�K�[�h�N���X

  \author Satofumi KAMIMURA

  $Id: LockGuard.h 783 2009-05-05 08:56:26Z satofumi $
*/

#include <memory>


namespace qrk
{
  class Lock;

  /*!
    \brief ���b�N�K�[�h�N���X
  */
  class LockGuard
  {
    LockGuard(void);
    LockGuard(const LockGuard& rhs);
    LockGuard& operator = (const LockGuard& rhs);

    void* operator new (size_t);
    void* operator new[] (size_t);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;

  public:
    /*!
      \brief �R���X�g���N�^

      \param[in] mutex �~���[�e�b�N�X����
    */
    explicit LockGuard(qrk::Lock& mutex);
    ~LockGuard(void);
  };
}

#endif /* !QRK_LOCK_GUARD_H */

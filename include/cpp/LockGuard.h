#ifndef QRK_LOCK_GUARD_H
#define QRK_LOCK_GUARD_H

/*!
  \file
  \brief ���b�N�K�[�h�N���X

  \author Satofumi KAMIMURA

  $Id: LockGuard.h 1954 2011-07-17 22:08:18Z satofumi $
*/

#include <memory>
#include <cstddef>


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

    //void* operator new (size_t);
    //void* operator new[] (size_t);

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

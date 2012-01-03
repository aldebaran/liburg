#ifndef QRK_LOCK_GUARD_H
#define QRK_LOCK_GUARD_H

/*!
  \file
  \brief ロックガードクラス

  \author Satofumi KAMIMURA

  $Id: LockGuard.h 783 2009-05-05 08:56:26Z satofumi $
*/

#include <memory>


namespace qrk
{
  class Lock;

  /*!
    \brief ロックガードクラス
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
      \brief コンストラクタ

      \param[in] mutex ミューテックス資源
    */
    explicit LockGuard(qrk::Lock& mutex);
    ~LockGuard(void);
  };
}

#endif /* !QRK_LOCK_GUARD_H */

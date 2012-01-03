#ifndef QRK_LOCK_H
#define QRK_LOCK_H

/*!
  \file
  \brief ���b�N�N���X

  \author Satofumi KAMIMURA

  $Id: Lock.h 1954 2011-07-17 22:08:18Z satofumi $
*/

#include "ConditionVariable.h"
#include <cstddef>


namespace qrk
{
  /*!
    \brief ���b�N�N���X
  */
  class Lock {

    friend class ConditionalVariable;
    friend bool ConditionVariable::wait(Lock* lock, int timeout);

    Lock(const Lock& rhs);
    Lock& operator = (const Lock& rhs);

    // !!!
    //void* operator new (size_t);
    //void* operator new[] (size_t);

    struct pImpl;
    const std::auto_ptr<pImpl> pimpl;

  public:
    Lock(void);
    ~Lock(void);


    /*!
      \brief ���b�N
    */
    void lock(void);


    /*!
      \brief ���b�N
    */
    bool tryLock(void);


    /*!
      \brief �A�����b�N
    */
    void unlock(void);
  };
}

#endif /* !QRK_LOCK_GUARD_H */

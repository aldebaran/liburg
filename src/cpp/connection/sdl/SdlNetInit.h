#ifndef QRK_SDL_NET_INIT_H
#define QRK_SDL_NET_INIT_H

/*!
  \file
  \brief SDL_net �̏�����

  \author Satofumi KAMIMURA

  $Id$
*/

#include <memory>


namespace qrk
{
    //! SDL_net �̏�����
    class SdlNetInit
    {
        SdlNetInit(const SdlNetInit& rhs);
        SdlNetInit& operator = (const SdlNetInit& rhs);

        struct pImpl;
        std::auto_ptr<pImpl> pimpl;

    protected:
        SdlNetInit(void);
        ~SdlNetInit(void);
    };
}

#endif /* !QRK_SDL_NET_INIT_H */

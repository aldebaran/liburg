#ifndef QRK_SCIP_UTILS_H
#define QRK_SCIP_UTILS_H

/*!
  \file

  \brief Reception of SCIP 2.0 response

  \author Satofumi KAMIMURA

  $Id: ScipUtils.h 1684 2010-02-10 23:56:38Z satofumi $
*/

#include <vector>
#include <string>


namespace qrk {
  class Connection;

  enum {
    ScipTimeout = 200,          //!< [msec]
  };
}


/*!
  \brief Decoding of SCIP data

  \param[in] code Characters to be decoded
  \param[in] byte Number of decoding characters

  \retval Decoding result
*/
extern int decode(const char code[], int byte);


/*!
  \brief Simple command transmission

  \param[in] con Connection object
  \param timeout Received timestamp [msec]
  \param[out] lines To store received data

  \retval 0 Normal
  retval < 0 Error
*/
extern int recvReply(qrk::Connection* con, int timeout,
                     std::vector<std::string>* lines = NULL);

#endif /* !QRK_SCIP_UTILS_H */

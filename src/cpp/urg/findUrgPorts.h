#ifndef QRK_FIND_URG_PORTS_H
#define QRK_FIND_URG_PORTS_H

/*!
  \file
  \brief URG �|�[�g�̎擾

  \author Satofumi KAMIMURA

  $Id: findUrgPorts.h 1386 2009-10-09 08:00:11Z satofumi $
*/

#include <vector>
#include <string>


namespace qrk
{
  /*!
    \brief URG �|�[�g�̎擾

    Example
    \code
    !!!
    !!! findUrgPorts()
    FindComPorts com_finder;
    !!! unique() �����̂Ȃɂ�
    !!! �L�q���邱��
    \endcode
  */
  size_t findUrgPorts(std::vector<std::string>& ports);
};

#endif /* !QRK_FIND_URG_PORTS_H */

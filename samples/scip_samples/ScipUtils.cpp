/*!
  \file

  \brief Reception of SCIP 2.0 response

  \author Satofumi KAMIMURA

  $Id: ScipUtils.cpp 1701 2010-02-16 05:33:25Z satofumi $
*/

#include "ScipUtils.h"
#include "Connection.h"
#include "ConnectionUtils.h"
#include <cstdlib>

using namespace qrk;
using namespace std;


int decode(const char code[], int byte)
{
  int value = 0;
  int i;

  for (i = 0; i < byte; ++i) {
    value <<= 6;
    value &= ~0x3f;
    value |= code[i] - 0x30;
  }
  return value;
}


static char addSum(const char* buf, size_t count)
{
  char sum = 0;
  for (size_t i = 0; i < count; ++i) {
    sum += buf[i];
  }
  return sum;
}


int recvReply(qrk::Connection* con, int timeout,
              std::vector<std::string>* lines)
{
  // Read echo back
  enum { LineMax = 64 + 1};
  char buffer[LineMax];
  int n = readline(con, buffer, LineMax, timeout);
  if (n <= 0) {
    return ReceiveTimeout;
  }

  // Read the response
  n = readline(con, buffer, LineMax, timeout);
  if (n <= 0) {
    return ReceiveTimeout;
  }

  // Check the checksum
  char checksum = (addSum(buffer, n - 1) & 0x3f) + 0x30;
  if (buffer[n - 1] != checksum) {
    return -3;
  }
  // Get status
  buffer[2] = '\0';
  int reply_code = strtol(buffer, NULL, 16);

  // read the new line character (1byte)
  char last_ch;
  n = con->receive(&last_ch, 1, timeout);
  if (n != 1) {
    return -4;
  }
  if (! isLF(last_ch)) {
    // If the character is not a line feed, then that character may be data.
    //  So write back that character.
    con->ungetc(last_ch);
  }

  // If "lines" is not a NULL, store as string data till the linefeed character.
  if (lines != NULL) {
    while (true) {
      n = readline(con, buffer, LineMax, timeout);
      lines->push_back(buffer);
      if ((n == 1) && isLF(buffer[0])) {
        break;

      } else if (n <= 0) {
        return -1;
      }
    }
  }

#if defined(WINDOWS_OS)
  getchar();
#endif

  return reply_code;
}

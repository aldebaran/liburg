/*!
  \file
  \brief �w��h���C�o�����p�����𔻒f����

  \author Satofumi KAMIMURA

  $Id: isUsingComDriver.cpp 1431 2009-10-20 13:33:03Z satofumi $
*/

#include "isUsingComDriver.h"
#include "DetectOS.h"
#ifdef WINDOWS_OS
#include <windows.h>
#include <string>
#endif

using namespace std;


#ifdef WINDOWS_OS
namespace
{
  bool existRegValue(HKEY hkey, LPCSTR subkey, const char* find_value)
  {
    HKEY next_hkey;
    if (RegOpenKeyExA(hkey, subkey, 0, KEY_READ, &next_hkey) != ERROR_SUCCESS) {
      return false;
    }
    enum { MaxLength = 1024 };

    // find_value �����݂��邩��T��
    CHAR device[MaxLength + 1];
    char name[MaxLength + 1];

    DWORD ret = ERROR_SUCCESS;
    for (int i = 0; ret == ERROR_SUCCESS; ++i) {
      DWORD dl = MaxLength;
      DWORD nl = MaxLength;
      ret = RegEnumValueA(hkey, i, device, &dl, NULL, NULL, (BYTE*)name, &nl);
      if (ret != ERROR_SUCCESS) {
        break;
      }
      if (! strncmp(name, find_value, nl)) {
        RegCloseKey(next_hkey);
        return true;
      }
    }

    // find_value �����݂��Ȃ���΁A�ċA�T�����s��
    char next_subkey[MaxLength];
    FILETIME filetime;

    ret = ERROR_SUCCESS;
    for (int i = 0; ret == ERROR_SUCCESS; ++i) {
      DWORD dl = MaxLength, nl = MaxLength;
      ret = RegEnumKeyExA(next_hkey, i, next_subkey,
                          &dl, NULL, NULL, &nl, &filetime);
      if (ret != ERROR_SUCCESS) {
        break;
      }

      bool value_exist = existRegValue(next_hkey, next_subkey, find_value);
      if (value_exist) {
        RegCloseKey(next_hkey);
        return true;
      }
    }

    RegCloseKey(next_hkey);
    return false;
  }
}


bool qrk::isUsingComDriver(const char* com_port, const char* driver_name)
{
  // �w�肵�����O�ƈ�v���邩���m�F����
  // !!!

  // �w��h���C�o���� �� Value �Ɋ܂܂�Ă��邩����
  string value_pattern = string(driver_name) + " (" + com_port + ")";
  if (existRegValue(HKEY_LOCAL_MACHINE,
                    "SYSTEM\\CurrentControlSet\\Enum\\USB",
                    value_pattern.c_str())) {
    return true;
  }
  return false;
}
#else

bool qrk::isUsingComDriver(const char* com_port, const char* driver_name)
{
  static_cast<void>(com_port);
  static_cast<void>(driver_name);

  return false;
}
#endif

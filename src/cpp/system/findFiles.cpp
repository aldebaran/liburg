/*!
  \file
  \brief �f�B���N�g���ȉ��̃t�@�C���T�����s��

  \author Satofumi KAMIMURA

  $Id: findFiles.cpp 772 2009-05-05 06:57:57Z satofumi $
*/

#include "findFiles.h"
#include <sys/types.h>
#include "DetectOS.h"
#ifdef MSC
#include <windows.h>
#else
#include <dirent.h>
#endif

using namespace boost;
using namespace xpressive;
using namespace std;


size_t qrk::findFiles(vector<string>& files, const char* root_path,
                      sregex pattern)
{
#ifdef MSC
  // !!! Windows ����
  WIN32_FIND_DATAA fd;
  string match_pattern = string(root_path) + "*";
  HANDLE dir = FindFirstFileA(match_pattern.c_str(), &fd);
  if (dir == INVALID_HANDLE_VALUE) {
    return 0;
  }
  size_t n = strlen(root_path);
  const char* add_str = (root_path[n -1] == '/') ? "" : "/";

  // �t�@�C�����Ƀp�^�[���Ƀ}�b�`���邩�̔�����s��
  size_t found_num = 0;

  do {
    string line = fd.cFileName;
    smatch match;
    if (regex_search(line, match, pattern)) {
      files.push_back(string(root_path) + add_str + line);
      ++found_num;
    }
  } while (FindNextFileA(dir, &fd));
  FindClose(dir);

  return found_num;

#else
  // Linux, MacOS ����
  DIR* dir = opendir(root_path);
  if (dir == NULL) {
    // !!! �G���[�o��
    return 0;
  }
  size_t n = strlen(root_path);
  const char* add_str = (root_path[n -1] == '/') ? "" : "/";

  // �t�@�C�����Ƀp�^�[���Ƀ}�b�`���邩�̔�����s��
  size_t found_num = 0;

  struct dirent* entry;
  while ((entry = readdir(dir)) != NULL) {
    string line = entry->d_name;
    smatch match;
    if (regex_search(line, match, pattern)) {
      files.push_back(string(root_path) + add_str + line);
      ++found_num;
    }
  }
  closedir(dir);
#endif

  return found_num;
}

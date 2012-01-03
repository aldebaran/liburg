#ifndef QRK_FIND_FILES_H
#define QRK_FIND_FILES_H

/*!
  \file
  \brief ディレクトリ以下のファイル探索を行う

  \author Satofumi KAMIMURA

  $Id: findFiles.h 1663 2010-02-01 07:17:58Z satofumi $
*/

#include <boost/xpressive/xpressive.hpp>
#include <vector>
#include <string>


namespace qrk
{
  /*!
    ディレクトリ以下のファイル探索を行う

    \param[out] files 見付かったファイル
    \param[in] root_path 探索のルートディレクトリ
    \param[in] pattern ファイルの検索パターン

    \return 見付かったファイル数
  */
  extern size_t findFiles(std::vector<std::string>& files,
                          const char* root_path,
                          const boost::xpressive::sregex pattern);
}

#endif /* !QRK_FIND_FILES_H */

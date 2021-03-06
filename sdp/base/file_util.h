#ifndef SDP_BASE_FILEUTIL_H
#define SDP_BASE_FILEUTIL_H

#include <iostream>

#include <sdp/base/error_code.h>

namespace sdp{

class FileUtil{
public:
  enum FileType {
    FILETYPE_REG     = 1,               //regular file
    FILETYPE_DIR     = 2,               //directory file
    FILETYPE_CHR     = 3,               //character special file
    FILETYPE_BLK     = 4,               //block special file
    FILETYPE_FIFO    = 5,               //pipe or FIFO
    FILETYPE_LNK     = 6,               //symbolic link
    FILETYPE_SOCK    = 7,               //socket

    FILETYPE_UNKNOW  = 9,
    FILETYPE_MAX     = 10,
  };

  enum CopyOption {
    FAIL_IF_EXISTS = 1,
    OVERWRITE_IF_EXISTS = 2,            //if directory just merge and overwrite if have a conflict.
    
    COPYOPTION_MAX = 10
  };

public:    
  static bool isDir(const std::string& path);

  //is regular file.
  static bool isFile(const std::string& path);

  static FileType getFileType(const std::string& path, ErrorCode& err);

  static size_t getFileSize(const std::string& path, ErrorCode& err);

  static bool createFile(const std::string& path, ErrorCode& err,
                         CopyOption = FAIL_IF_EXISTS);

  //no recursion.
  static bool createDir(const std::string& path, ErrorCode& err, 
                        CopyOption = FAIL_IF_EXISTS);

  static bool removeFile(const std::string& path, ErrorCode& err);

  static bool removeDir(const std::string& path, ErrorCode& err);

  static bool moveFile(const std::string& from_path, const std::string& to_path,
                       ErrorCode& err, CopyOption = FAIL_IF_EXISTS);

  static bool moveDir(const std::string& from_path, const std::string& to_path,
                      ErrorCode& err, CopyOption = FAIL_IF_EXISTS);

  static bool copyFile(const std::string& from_path, const std::string& to_path, 
                       ErrorCode& err, CopyOption = FAIL_IF_EXISTS);
  
  static bool copyDir(const std::string& from_path, const std::string& to_path,
                      ErrorCode& err, CopyOption = FAIL_IF_EXISTS);
};
}

#endif  //end of SDP_BASE_FILEUTIL_H

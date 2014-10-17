#ifndef SDP_BASE_FILEUTIL_H
#define SDP_BASE_FILEUTIL_H

#include <iostream>

namespace sdp{

class FileUtil{
public:
    enum FileType {
        FILETYPE_REG     = 1,    //regular file
        FILETYPE_DIR     = 2,    //directory file
        FILETYPE_CHR     = 3,    //character special file
        FILETYPE_BLK     = 4,    //block special file
        FILETYPE_FIFO    = 5,    //pipe or FIFO
        FILETYPE_LNK     = 6,    //symbolic link
        FILETYPE_SOCK    = 7,    //socket

        FILETYPE_UNKNOW  = 9,
        FILETYPE_MAX     = 10,
    };

public:    
    static bool isDir(const std::string& path);

    //is regular file.
    static bool isFile(const std::string& path);

    static FileType getFileType(const std::string& path);

    static bool createFile(const std::string& path);

    static bool createDir(const std::string& path);

    static bool removeFile(const std::string& path);

    static bool removeDir(const std::string& path);

    static bool moveFile(const std::string& from_path, const std::string& to_path);

    static bool moveDir(const std::string& from_path, const std::string& to_path);

    static bool copyFile(const std::string& from_path, const std::string& to_path);

    static bool copyDir(const std::string& from_path, const std::string& to_path);

    static bool mergeDir(const std::string& from_path, const std::string& to_path);
};
}

#endif  //end of SDP_BASE_FILEUTIL_H

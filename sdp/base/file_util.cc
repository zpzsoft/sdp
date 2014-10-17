#include <sdp/base/file_util.h>

#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

namespace sdp{

bool FileUtil::isDir(const std::string& path)
{
    struct stat st;
    
    if (stat(path.c_str(), &st) != -1 && S_ISDIR(st.st_mode))
        return true;
    
    return false;
}

bool FileUtil::isFile(const std::string& path)
{
    struct stat st;
    
    if (stat(path.c_str(), &st) != -1 && S_ISREG(st.st_mode))
        return true;

    return false;
}

FileUtil::FileType FileUtil::getFileType(const std::string& path)
{
    struct stat st;
    FileType file_type = FILETYPE_UNKNOW;
    
    if (stat(path.c_str(), &st) == -1 )
        return file_type;

    if( S_ISREG(st.st_mode))
        file_type = FILETYPE_REG;
    else if (S_ISDIR(st.st_mode))
        file_type = FILETYPE_DIR;
    else if (S_ISCHR(st.st_mode))
        file_type = FILETYPE_CHR;
    else if (S_ISBLK(st.st_mode))
        file_type = FILETYPE_BLK;
    else if (S_ISFIFO(st.st_mode))
        file_type = FILETYPE_FIFO;
    else if (S_ISLNK(st.st_mode))
        file_type = FILETYPE_LNK;
    else if (S_ISSOCK(st.st_mode))
        file_type = FILETYPE_SOCK;

    return file_type;
}
    
bool FileUtil::createFile(const std::string& path)
{
    if (path.empty())
        return false;

    std::string dir_path = path.substr(0, path.find_last_of("/"));

    if (!isDir(dir_path))
        return false;

    //current process wheather have permision to access this directory.
    if (access(dir_path.c_str(), R_OK | W_OK) < 0)
        return false;

    bool ret = true;
    FILE *file = fopen(path.c_str(), "r");

    if (file)
        ret = false;
    else{
        file = fopen(path.c_str(), "w+");
        
        if(file == NULL)
            return false;
    }

    fclose(file);
    
    return ret;
}

bool FileUtil::createDir(const std::string& path)
{
    int ret = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH |S_IXOTH);

    if (ret == 0)
        return true;

    return false;
}

bool FileUtil::removeFile(const std::string& path)
{
    if (remove(path.c_str()) == 0)
        return true;

    return false;
}

bool FileUtil::removeDir(const std::string& path)
{        
    DIR *dir = NULL;
    struct dirent *entry = NULL;
  
    if (!(dir = opendir(path.c_str())))
        return false;
    
    while ((entry = readdir(dir)) != NULL) {
        struct stat sb;
        std::string current_path = path + "/" + std::string(entry->d_name);
        
        lstat(current_path.c_str(), &sb);
     
        if (S_IFDIR == (sb.st_mode & S_IFMT)) {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;
            
            if (!removeDir(current_path))
                return false;
        }
        else {
            if (remove(current_path.c_str()) != 0)
                return false;
        }        
    }

    if(rmdir(path.c_str()) != 0)
        return false;
    
    return true;
}    
}

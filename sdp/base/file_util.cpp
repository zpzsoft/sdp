#include <sdp/base/file_util.h>

#include <iostream>
#include <fstream>
#include <string.h>

#if defined(__linux) || defined(__APPLE__)
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#endif

namespace sdp{

bool error(bool was_error, ErrorCode& ec, Errc err, const std::string& message)
{
  if (!was_error)
    ec.clear();
  else  
    ec.assign(err, message);

  return was_error;
}

bool error(bool was_error, ErrorCode& ec, ErrorCode& other)
{
  if (!was_error)
    ec.clear();
  else  
    ec = other;

  return was_error;
}


bool FileUtil::isDir(const std::string& path)
{
#if defined(__linux) || defined(__APPLE__)
  struct stat st;
    
  if (::stat(path.c_str(), &st) != -1 && S_ISDIR(st.st_mode))
    return true;
#endif
  
  return false;
}

bool FileUtil::isFile(const std::string& path)
{
#if defined(__linux) || defined(__APPLE__)
  struct stat st;
    
  if (::stat(path.c_str(), &st) != -1 && S_ISREG(st.st_mode))
    return true;
#endif

  return false;
}

FileUtil::FileType FileUtil::getFileType(const std::string& path, 
                                         ErrorCode& err)
{
  FileType file_type = FILETYPE_UNKNOW;
#if defined(__linux) || defined(__APPLE__)
  struct stat st;
    
  if (!error(::stat(path.c_str(), &st) == -1, err, 
             NO_SUCH_FILE_OR_DIRECTORY,
             "FileUtil::getFileType"))
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
#endif
  return file_type;
}

size_t FileUtil::getFileSize(const std::string& path, ErrorCode& err) {
  size_t size = 0;
#if defined(__linux) || defined(__APPLE__)
  struct stat st;
  
  if (::stat(path.c_str(), &st) == 0)
    size = st.st_size;
#endif
  
  return size;
}
bool FileUtil::createFile(const std::string& path,ErrorCode& err,
                          CopyOption option)
{
  std::string dir_path = path.substr(0, path.find_last_of("/"));

  if (error(dir_path.empty() || !isDir(dir_path), err, 
             NO_SUCH_FILE_OR_DIRECTORY, 
            "FileUtil::createFile"))
    return false;

#if defined(__linux) || defined(__APPLE__)
  if (error(::access(dir_path.c_str(), R_OK | W_OK) < 0, err, 
             OPERATION_NOT_PERMITTED,
            "FileUtil::createFile"))
#endif
    return false;

  bool ret = true;
  FILE *file = ::fopen(path.c_str(), "r");

  if (file) {
    ::fclose(file);
    
    if (error(option == FAIL_IF_EXISTS, err, FILE_EXISTS, 
              "FileUtil::create file"))
      return false;
  }

  file = ::fopen(path.c_str(), "w+");
  if (error(file == NULL, err, Errc(errno), "FileUtil::createFile"))
    return false;

  ::fclose(file);
    
  return ret;
}

bool FileUtil::createDir(const std::string& path, ErrorCode& err,
                         CopyOption option)
{
  int ret;
  if (error(option == FAIL_IF_EXISTS && isDir(path), 
            err, FILE_EXISTS, 
            "FileUtil::createDir"))
    return false;
  
#if defined(__linux) || defined(__APPLE__)
  if (option == OVERWRITE_IF_EXISTS && isDir(path)) {
    if (error(::access(path.c_str(), R_OK | W_OK) < 0, err, 
             OPERATION_NOT_PERMITTED,
             "FileUtil::createDir"))
      return false;
    else
      return true;
  }

  ret = ::mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH |S_IXOTH);
#else
  return false;
#endif

  if (error(ret != 0, err, Errc(errno), "FileUtil::createDir"))
    return false;
  return true;
}

bool FileUtil::removeFile(const std::string& path, ErrorCode& err)
{
#if defined(__linux) || defined(__APPLE__)
  if (!error(::remove(path.c_str()) != 0, err, Errc(errno), "FileUtil::removeFile"))
    return true;
#endif
  
  return false;
}

bool FileUtil::removeDir(const std::string& path, ErrorCode& err)
{
#if defined(__linux) || defined(__APPLE__)  
  DIR *dir = NULL;
  struct dirent *entry = NULL;
 
  if (!(dir = ::opendir(path.c_str())))
    return false;
    
  while ((entry = ::readdir(dir)) != NULL) {
    struct stat sb;
    std::string current_path = path + "/" + std::string(entry->d_name);
        
    ::lstat(current_path.c_str(), &sb);
     
    if (S_IFDIR == (sb.st_mode & S_IFMT)) {
      if (::strcmp(".", entry->d_name) == 0 || ::strcmp("..", entry->d_name) == 0)
        continue;
      
      ErrorCode remove_dir_error;
      if (error(!removeDir(current_path, remove_dir_error), err, remove_dir_error))
        return false;
    }
    else {
      ErrorCode remove_file_error;
      if (error(!removeFile(current_path, remove_file_error), err, remove_file_error))
        return false;
    }        
  }

  if (error(::rmdir(path.c_str()) != 0, err, Errc(errno),
            "FileUtil::removeDir"))
    return false;
    
  return true;
#else
  return false;
#endif
}

bool FileUtil::moveFile(const std::string& from_path, 
                        const std::string& to_path, 
                        ErrorCode& err,
                        CopyOption option)
{
  int ret;
  
  if (!isFile(from_path)) {
    err.assign(NO_SUCH_FILE_OR_DIRECTORY, "File::moveFile");
    return false;
  }
  
  if (isFile(to_path)) {
    if (option == FAIL_IF_EXISTS) {
      err.assign(FILE_EXISTS, "FileUtil::moveFile");
      return false;
    } else if (option == OVERWRITE_IF_EXISTS) {
      ErrorCode remove_file_error;
      if (error(!removeFile(to_path, remove_file_error),
                err, remove_file_error))
        return false;
    }
  }

#if defined(__linux) || defined(__APPLE__)
  ret = ::rename(from_path.c_str(), to_path.c_str());
#else
  return false;
#endif

  if (error(ret != 0, err, Errc(errno), "FileUtil::moveFile"))
    return false;
  
  return true;
}

bool FileUtil::moveDir(const std::string& from_path, 
                       const std::string& to_path, 
                       ErrorCode& err,
                       CopyOption option)
{
  if (error(!isDir(from_path), err, NO_SUCH_FILE_OR_DIRECTORY,
            "FileUtil::moveDir"))
    return false;
  
  if (error(option == FAIL_IF_EXISTS && isDir(to_path), 
            err, FILE_EXISTS, "FileUtil::moveDir"))
    return false;
  
  ErrorCode copy_dir_error;
  ErrorCode remove_dir_error;
  if (error(!copyDir(from_path, to_path, copy_dir_error,
                     option), err, copy_dir_error))
    return false;
  if (error(!removeDir(from_path,remove_dir_error),
            err, remove_dir_error))
    return false;
  
  return true;
}

bool FileUtil::copyFile(const std::string& from_path, const std::string& to_path,
                        ErrorCode& err, CopyOption option)
{
  const std::size_t buf_size = 8196;
  char buf[buf_size];
  FILE *infile = NULL, *outfile = NULL;
  
  infile = fopen(from_path.c_str(), "r");
  if (error(infile == NULL, err, NO_SUCH_FILE_OR_DIRECTORY, 
            "FileUtil:copyFile"))
    return false;

  if (isFile(to_path)) {
    if (option == FAIL_IF_EXISTS) {
      err.assign(FILE_EXISTS, "FileUtil::copyFile");
      return false;
    } else if (option == OVERWRITE_IF_EXISTS) {
      ErrorCode remove_file_error;
      if (error(!removeFile(to_path, remove_file_error), err, remove_file_error))
        return false;
    }
  }

  outfile = fopen(to_path.c_str(), "w+");
  if (error(outfile == NULL, err, 
            RESOURCE_UNAVAILABLE_TRY_AGAIN,
            "FileUtil::copyFile"))
    return false;
            
  size_t sz, sz_read = 1, sz_write = 0;
  while (sz_read) {
    memset(buf, 0, buf_size);
    sz_read = fread(buf, 1, buf_size, infile);

    if (sz_read < 0)
      break;

    sz_write = 0;
    do {
      sz = fwrite(buf + sz_write, 1, sz_read - sz_write, outfile);
      sz_write += sz;
    }while(sz_write < sz_read);
  }
    
  return true;
}

bool FileUtil::copyDir(const std::string& from_path, const std::string& to_path,
                       ErrorCode& err, CopyOption option)
{
#if defined(__linux) || defined(__APPLE__)
  DIR *dir = NULL;
  struct ::dirent *entry = NULL;

  if (error(!(dir = ::opendir(from_path.c_str())), err, 
            RESOURCE_UNAVAILABLE_TRY_AGAIN,
            "FileUtil::copyDir"))
    return false;

  if (isDir(to_path)) {
    if (option == FAIL_IF_EXISTS) {
      err.assign(FILE_EXISTS, "FileUtil::copyDir");
      return false;
    }
  } else {
    int ret = ::mkdir(to_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    if (error(ret != 0, err, Errc(errno), "FileUtil::copyDir make dir failed."))
      return false;
  }
    
  while ((entry = ::readdir(dir)) != NULL) {
    struct stat sb;
    std::string current_path = from_path + "/" + std::string(entry->d_name);
    std::string target_path = to_path + "/" + std::string(entry->d_name);
        
    ::lstat(current_path.c_str(), &sb);
        
    if (S_IFDIR == (sb.st_mode & S_IFMT)) {
      if (::strcmp(".", entry->d_name) == 0 || ::strcmp("..", entry->d_name) == 0)
        continue;
      
      ErrorCode copy_dir_error;
      if (error(!copyDir(current_path.c_str(), target_path.c_str(), copy_dir_error, option), err, copy_dir_error))
        return false;
    }
    else {
      ErrorCode copy_file_error;
      if (!error(copyFile(current_path, target_path, copy_file_error, option), err, copy_file_error))
        return false;
    }
  }
    
  return true;
#else
  return false;
#endif
}    
}

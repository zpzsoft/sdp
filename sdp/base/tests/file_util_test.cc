#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <sdp/base/file_util.h>

using namespace sdp;

int main(int argc, char ** argv)
{
  if( argc < 2)
    printf("lack of parameters \n");
    
  printf("1, test is file.\n\
2, test is dir.\n\
3, test create file.\n\
4, test create dir. \n\
5, test remove file.\n\
6, test remove dir.\n\
7, test get file type.\n\
8, test copy file.\n\
9, test copy dir.\n\
10,test move file.\n\
11,test move dir.\n\
");

  printf("take a choice :\n");

  char* test_path = argv[1];

  char input[1024] = {0};
  while (gets(input)) {
    int choice = atoi(input);
    switch (choice) {
    case 1: {
      bool ret = FileUtil::isFile(test_path);
      printf("path %s is file ? %d\n", test_path, ret);
      break;
    }
    case 2: {
      bool ret = FileUtil::isDir(test_path);
      printf("path %s is dir ? %d\n", test_path, ret);
      break;
    }
    case 3: {
      ErrorCode error;
      bool ret = FileUtil::createFile(test_path, error, FileUtil::OVERWRITE_IF_EXISTS);
      printf("create file at path %s get ret : %d\n", test_path, ret);
      break;
    }
    case 4: {
      ErrorCode error;
      bool ret = FileUtil::createDir(test_path, error, FileUtil::OVERWRITE_IF_EXISTS);
      printf("create dir at path %s get ret : %d\n", test_path, ret);
      break;
    }
    case 5: {
      ErrorCode error;
      bool ret = FileUtil::removeFile(test_path, error);
      printf("remove file at path %s get ret : %d\n", test_path, ret);
      break;
    }
    case 6: {
      ErrorCode error;
      bool ret = FileUtil::removeDir(test_path, error);
      printf("remove dir at path %s get ret : %d\n", test_path, ret);
      break;
    }
    case 7: {
      ErrorCode error;
      FileUtil::FileType type = FileUtil::getFileType(test_path, error);
      printf("get file type : %d at path :%s \n", type, test_path);
    }
    case 8: {
      if (argc < 3)
        printf("copy file need output path\n");
      else {
        char* out_path = argv[2];
        ErrorCode error;
        bool ret = FileUtil::copyFile(test_path, out_path, error, FileUtil::OVERWRITE_IF_EXISTS);
        printf("copy file ret :%d\n", ret);
      }
      break;
    }
    case 9: {
      if (argc < 3)
        printf("copy dir need output path\n");
      else {
        char* out_path = argv[2];
        ErrorCode error;
        bool ret = FileUtil::copyDir(test_path, out_path, error, FileUtil::OVERWRITE_IF_EXISTS);
        printf("copy dir ret :%d with  error :%s\n", ret, error.get_msg().c_str());
      }

      break;
    }
    case 10: {
      if (argc < 3)
        printf("copy dir need output path\n");
      else {
        char* out_path = argv[2];
        ErrorCode error;
        
        bool ret = FileUtil::moveFile(test_path, out_path, error, FileUtil::OVERWRITE_IF_EXISTS);
        printf("move file get ret:%d\n", ret);
      }
      break;
    }
    case 11: {
      if (argc < 3)
        printf("copy dir need output path\n");
      else {
        char* out_path = argv[2];
        ErrorCode error;

        bool ret = FileUtil::moveDir(test_path, out_path, error, FileUtil::OVERWRITE_IF_EXISTS);
        printf("move dir get ret :%d\n", ret);
      }
      break;
    }
    default:
      break;
    }

    break;
  }
    
  return 1;
}

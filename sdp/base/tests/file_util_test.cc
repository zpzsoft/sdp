#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <sdp/base/file_util.h>

using namespace sdp;

int main(int argc, char ** argv)
{
    if( argc < 2)
        printf("lack of parameters \n");
    
    //initscr();
    printf("1, test is file.\n\
2, test is dir.\n\
3, test create file.\n\
4, test create dir. \n\
5, test create remove file.\n\
6, test create remove dir.\n\
7, test get file type.\n\
8, test copy file.\n\
9, test copy dir.\n\
");

    printf("take a choice :\n");

    char* test_path = argv[1];

    char ch;
    while (ch = getchar()) {
        switch (ch) {
        case '1': {
            bool ret = FileUtil::isFile(test_path);
            printf("path %s is file ? %d\n", test_path, ret);
            break;
        }
        case '2': {
            bool ret = FileUtil::isDir(test_path);
            printf("path %s is dir ? %d\n", test_path, ret);
            break;
        }
        case '3': {
            bool ret = FileUtil::createFile(test_path);
            printf("create file at path %s get ret : %d\n", test_path, ret);
            break;
        }
        case '4': {
            bool ret = FileUtil::createDir(test_path);
            printf("create dir at path %s get ret : %d\n", test_path, ret);
            break;
        }
        case '5': {
            bool ret = FileUtil::removeFile(test_path);
            printf("remove file at path %s get ret : %d\n", test_path, ret);
            break;
        }
        case '6': {
            bool ret = FileUtil::removeDir(test_path);
            printf("remove dir at path %s get ret : %d\n", test_path, ret);
            break;
        }
        case '7': {
            FileUtil::FileType type = FileUtil::getFileType(test_path);
            printf("get file type : %d at path :%s \n", type, test_path);
        }
        case '8': {
            if (argc < 3)
                printf("copy file need output path\n");
            else {
                char* out_path = argv[2];
                bool ret = FileUtil::copyFile(test_path, out_path);
                printf("copy file ret :%d\n", ret);
            }
            break;
        }
        case '9': {
            if (argc < 3)
                printf("copy dir need output path\n");
            else {
                char* out_path = argv[2];
                bool ret = FileUtil::copyDir(test_path, out_path);
                printf("copy dir ret :%d\n", ret);
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

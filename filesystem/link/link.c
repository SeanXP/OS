/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < link.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/26 >
  > Description:       文件硬链接以及符号链接函数联系

    link - make a new name for a file

        #include <unistd.h>
        int link(const char *oldpath, const char *newpath);

    link() creates a new link (also known as a hard link) to an existing file.
    If newpath exists, it will not be overwritten.

    成功返回0，失败返回-1并设置errno；
    若newpath已存在，则失败并设置errno为EEXIST;
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s source link\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(link(argv[1], argv[2]) == -1)
    {
        if(errno == EEXIST)
            fprintf(stderr, "File exists!\n");
        else
            perror("link() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < fcntl.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/12 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_MAX_LEN  1024
#define FILE_NAME      "./hello.txt"

int main(int argc, char* argv[])
{
    char buffer[BUFFER_MAX_LEN + 1];
    ssize_t ret;
    int fd;

    //{{{ open file read only.
    if((fd = open(FILE_NAME, O_RDONLY)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    //}}}
    //{{{ fcntl file
    int flags, accessMode;
    // F_GETFD / F_SETFD, 获得/设置描述符标记;
    if((flags = fcntl(fd, F_GETFL)) == -1)
    {
        perror("fcntl() error");
        exit(EXIT_FAILURE);
    }
    if(flags & O_SYNC)
        printf("\t O_SYNC, synchronized\n");
    // 判断访问模式, 由于O_RDONLY(0),O_WRONLY(1),O_RDWR(2)不在flags中的单独比特位，所以判断较麻烦
    // 需要使用掩码O_ACCMODE
    accessMode = flags & O_ACCMODE;
    if(accessMode == O_RDONLY)
        printf("\t O_RDONLY, read only.\n");
    else if(accessMode == O_WRONLY)
        printf("\t O_WRONLY, write only.\n");
    else if(accessMode == O_RDWR)
        printf("\t O_RDWR, read & write.\n");
    else
        printf("\t other access mode.\n");
    //}}}

    close(fd);
    return 0;
}

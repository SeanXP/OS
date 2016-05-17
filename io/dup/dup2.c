/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < dup2.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/17 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_MAX_LEN  1024
#define FILE_NAME      "./hello.txt"

int main(int argc, char* argv[])
{
    char buffer[BUFFER_MAX_LEN + 1] = "hello";
    ssize_t ret;
    int fd, dupfd;

    //{{{ create new file
    if((fd = open(FILE_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    printf("create new file: %s, fd = %d\n", FILE_NAME, fd);
    //}}}
    //{{{ dup2() to new fd - 20
    if((dupfd = dup2(fd, 20)) == -1)
    {
        perror("dup() error");
        exit(EXIT_FAILURE);
    }
    printf("dup file: oldfd = %d, dupfd = %d\n", fd, dupfd);
    //}}}
    //{{{ write to fd & close
    if((ret = write(fd, buffer, strlen(buffer))) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    close(fd);
    printf("write to [fd:%d] and close.\n", fd);
    //}}}
    //{{{ write to dupfd & close
    if((ret = write(dupfd, buffer, strlen(buffer))) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    close(dupfd);
    printf("write to [fd:%d] and close.\n", dupfd);
    //}}}

    return 0;
}

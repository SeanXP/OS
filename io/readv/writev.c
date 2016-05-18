/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < writev.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/18 >
  > Description:       writev() - 集中输出

    #include <sys/uio.h>
    ssize_t writev(int fildes, const struct iovec *iov, int iovcnt);

    wrtiev()实现集中输出功能：将 iov 所指定的缓冲区的数据拼接起来，以连续的字节序列写入文件描述符 fd 所指代的文件中。
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>         // exit()
#include <unistd.h>         // read(), pread(), close()
#include <fcntl.h>          // O_RDONLY
#include <sys/uio.h>        // readv(), writev()

#define BUFFER_MAX_LEN  1024
#define FILE_NAME       "./test.dat"

int main(int argc, char* argv[])
{
    int fd;
    ssize_t ret;
    struct iovec iov[3];
    /*
    struct iovec {
        char   *iov_base;  // Base address./
        size_t iov_len;    // Length.
    };
    */
    int ival = 1234;
    double dval = 0.1234;
    char buffer[] = "hello world";

    iov[0].iov_base = &ival;
    iov[0].iov_len = sizeof(ival);
    iov[1].iov_base = &dval;
    iov[1].iov_len = sizeof(dval);
    iov[2].iov_base = buffer;
    iov[2].iov_len = sizeof(buffer);

    if((fd = open(FILE_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    ret = writev(fd, iov, 3);
    printf("writev %ld bytes to file %s.\n", ret, FILE_NAME);

    close(fd);
    return 0;
}

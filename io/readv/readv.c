/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < readv.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/18 >
  > Description:       readv() - 分散输入
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>         // exit()
#include <unistd.h>         // read(), pread(), close()
#include <fcntl.h>          // O_RDONLY
#include <sys/uio.h>        // readv()

#define BUFFER_MAX_LEN  1024
#define FILE_NAME      "./test.dat"
// file date format: int, double, char[];

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
    int ival;
    double dval;
    char buffer[BUFFER_MAX_LEN + 1];

    iov[0].iov_base = &ival;
    iov[0].iov_len  = sizeof(int);
    iov[1].iov_base = &dval;
    iov[1].iov_len  = sizeof(double);
    iov[2].iov_base = buffer;
    iov[2].iov_len  = BUFFER_MAX_LEN;

    // open file
    if((fd = open(FILE_NAME, O_RDONLY)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }

    // readv form file
    if((ret = readv(fd, iov, 3)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }

    printf("readv %ld from file %s.\n", ret, FILE_NAME);
    printf("int value: %d\n", ival);
    printf("double value: %f\n", dval);
    printf("char[] value: [%s]\n", buffer);

    close(fd);
    return 0;
}

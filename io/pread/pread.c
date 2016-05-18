/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < pread.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/18 >
  > Description:        pread() - 指定offset的read(), 且不影响文件的当前偏移量;
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

    // open file
    if((fd = open(FILE_NAME, O_RDONLY)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }

    // read file
    if((ret = read(fd, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);

    // pread file
    if((ret = pread(fd, buffer, BUFFER_MAX_LEN, 13)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';
    printf("I pread %ld bytes.\n%s\n", ret, buffer);

    // read file again, test file offset.
    if((ret = read(fd, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);

    close(fd);
    return 0;
}

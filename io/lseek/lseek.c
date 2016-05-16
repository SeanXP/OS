/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < lseek.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/16 >
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
#define FILE_NAME1      "./hello.txt"
#define FILE_NAME2      "./test.txt"

int main(int argc, char* argv[])
{
    char buffer[BUFFER_MAX_LEN + 1];
    ssize_t ret;
    int fd;

    //{{{ open & read from file
    if((fd = open(FILE_NAME1, O_RDONLY)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    if((ret = read(fd, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);
    //}}}

    // read from end of file.
    printf("read from end of file.\n");
    //{{{ read from file
    if((ret = read(fd, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);
    //}}}

    printf("lseek to (start of file).\n");
    lseek(fd, 0, SEEK_SET);
    //{{{ read from file
    if((ret = read(fd, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);
    //}}}
    close(fd);

    printf("create new file and lseek to 1000 and write something.\n");
    printf("write to file: %s\n", FILE_NAME2);
    if((fd = open(FILE_NAME2, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    lseek(fd, 1000, SEEK_SET);
    if((ret = write(fd, buffer, strlen(buffer))) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}

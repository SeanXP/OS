/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < write.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/12 >
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
#define FILE_NAME1      "./tmp.txt"

int main(int argc, char* argv[])
{
    char buffer[BUFFER_MAX_LEN + 1];
    ssize_t ret;
    int fd;

    //{{{ read from stdio
    printf("STDIN_FILENO: %d\n", STDIN_FILENO);
    printf("Now, I am going to read string from stdin!\n");
    //ssize_t read(int fildes, void *buf, size_t nbyte);
    if((ret = read(STDIN_FILENO, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);
    //}}}
    //{{{ write to new file
    printf("write to file: %s\n", FILE_NAME1);
    if((fd = open(FILE_NAME1, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    if((ret = write(fd, buffer, strlen(buffer))) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    close(fd);
    //}}}
    return 0;
}

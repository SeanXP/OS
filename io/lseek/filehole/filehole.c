/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < filehole.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/16 >
  > Description:        use lseek() to create file holes.
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_MAX_LEN  1024
#define HOLE_OFFSET     200000
#define FILE_NAME      "./hole.txt"

int main(int argc, char* argv[])
{
    char buffer[BUFFER_MAX_LEN + 1];
    ssize_t ret;
    int fd;

    printf("create new file and lseek to %d and write something.\n", HOLE_OFFSET);
    if((fd = open(FILE_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    lseek(fd, HOLE_OFFSET, SEEK_SET);
    strcpy(buffer, "hello");
    if((ret = write(fd, buffer, strlen(buffer))) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}

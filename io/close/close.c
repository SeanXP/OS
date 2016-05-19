/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < close.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/19 >
  > Description:
 ****************************************************************/

#include<stdio.h>  // void perror(const char * s);
#include<unistd.h> // int close(int fd);

// close() 成功返回0，失败返回-1并设置errno.
// errno = EBADF 表示fd是无效的, Bad file descriptor
// errno = EINTR 表示close操作被信号终端. 详见single.
int main(int argc, char* argv[])
{

    int fd = -1;

    if(close(fd) == -1)
        perror("close() error");
    return 0;
}


/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < pathconf.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/23 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void print_fpathconf(const char *msg, int fd, int name)
{
    long lim;

    errno = 0;              // 必须先设置errno为0，以便检查是否错误；
    lim = fpathconf(fd, name);

    // 根据返回值输出结果
    if(lim != -1)
    {
        printf("%s\t\t%ld\n", msg, lim);
    } else {
        if(errno == 0)
            fprintf(stderr, "%s (indeterminate)\n", msg);
        else
        {
            perror("fpathconf() error");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char* argv[])
{
    print_fpathconf("_SC_ARG_MAX:", STDIN_FILENO, _SC_ARG_MAX);
    print_fpathconf("_PC_NAME_MAX:", STDIN_FILENO, _PC_NAME_MAX);
    return 0;
}

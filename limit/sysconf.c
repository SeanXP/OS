/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < sysconf.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/23 >
  > Description:

  long sysconf(int name);
  Returns value of limit specified by name, or -1 if limit is indeterminate or an error occurred.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void print_sysconf(const char *msg, int name)
{
    long lim;

    errno = 0;              // 必须先设置errno为0，以便检查是否错误；
    lim = sysconf(name);

    // 根据返回值输出结果
    if(lim != -1)
    {
        printf("%s\t\t%ld\n", msg, lim);
    } else {
        if(errno == 0)
            fprintf(stderr, "%s (indeterminate)\n", msg);
        else
        {
            perror("sysconf() error");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char* argv[])
{
    print_sysconf("_SC_ARG_MAX:",           _SC_ARG_MAX);
    print_sysconf("_SC_LOGIN_NAME_MAX:",    _SC_LOGIN_NAME_MAX);
    print_sysconf("_SC_OPEN_MAX:",          _SC_OPEN_MAX);
    print_sysconf("_SC_PAGESIZE:",          _SC_PAGESIZE);
    return 0;
}

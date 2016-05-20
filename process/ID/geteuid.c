/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < geteuid.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/20 >
  > Description:    geteuid, getuid -- get user identification
 ****************************************************************/

#include <stdio.h>
#include <unistd.h>     // getuid(), geteuid()

int main(int argc, char* argv[])
{
    printf("uid = %d\n", getuid());
    printf("gid = %d\n", getgid());
    printf("euid = %d\n", geteuid());
    printf("egid = %d\n", getegid());
    return 0;
}

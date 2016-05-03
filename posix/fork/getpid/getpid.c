/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < getpid.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/03 >
  > Description:
 ****************************************************************/
#include<stdio.h>
#include<unistd.h>      // getpid(), getppid()...

int main(int argc, char* argv[])
{
    printf("PID:  %ld\n", (long)getpid());
    printf("PPID: %ld\n", (long)getppid());
    printf("UID:  %ld\n", (long)getuid());
    printf("EUID: %ld\n", (long)geteuid());
    printf("GID:  %ld\n", (long)getgid());
    printf("EGID: %ld\n", (long)getegid());

    return 0;
}

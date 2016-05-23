/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < umount.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/23 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s target\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(umount(argv[1]) == -1)
    {
        perror("umount() error");
        exit(EXIT_FAILURE);
    }
    return 0;
}

/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < umount2.c >
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
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s target [flags]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // MNT_DETACH, lazy umount;
    // MNT_FORCE, force umount;
    if(umount2(argv[1], MNT_DETACH) == -1)
    {
        perror("umount2() error");
        exit(EXIT_FAILURE);
    }
    return 0;
}

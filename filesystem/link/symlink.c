/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < symlink.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/26 >
  > Description:       符号链接
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s source symlink\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(symlink(argv[1], argv[2]) == -1)
    {
        perror("symlink() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}


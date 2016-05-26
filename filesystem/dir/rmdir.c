/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < mkdir.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/26 >
  > Description:       删除空文件夹 rmdir()

     #include <unistd.h>

     int rmdir(const char *pathname);
     On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

 rmdir() deletes a directory, which must be empty.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s pathname\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(rmdir(argv[1]) == -1)
    {
        perror("rmdir() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}


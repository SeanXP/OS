/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < mkdir.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/26 >
  > Description:       新建文件夹 mkdir()

     #include <sys/stat.h>
     #include <sys/types.h>

     int mkdir(const char *pathname, mode_t mode);
 `mkdir()`创建一个新目录`pathname`，若路径名已存在，则返回-1并设置errno为`EEXIST`。
 `mode`参数决定新目录的权限。

 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s pathname\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(mkdir(argv[1], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP) == -1)
    {
        perror("mkdir() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}


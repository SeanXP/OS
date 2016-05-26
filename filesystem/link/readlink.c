/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < unlink.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/26 >
  > Description:       读取符号链接函数

 readlink - read value of a symbolic link

     #include <unistd.h>
     ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);
     Return number of bytes placed in buf on success, or -1 on error;

 将符号链接文件的内容读取到buf中。

 `read()`调用的参数如果是符号链接，则打开的是链接所指向的文件，而非链接文件本身。如果要打开链接文件本身，需要使用`readlink()`；
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_MAX    255

int main(int argc, char *argv[])
{
    char buffer[PATH_MAX];

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s link\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(readlink(argv[1], buffer, PATH_MAX) == -1)
    {
        perror("unlink() error");
        exit(EXIT_FAILURE);
    }
    printf("read link %s -> %s\n", argv[1], buffer);

    return 0;
}

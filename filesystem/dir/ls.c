/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < ls.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/26 >
  > Description:       目录访问函数练习 - ls 实现

    DIR *opendir(const char *dirname);
    成功则返回一个指向目录对象的指针，不成功返回空指针并设置errno.
    DIR 表一个目标流. directory stream. 特定目录中所有目录项组成的一个有序序列.

    struct dirent *readdir(DIR *dirp);
    通过返回dirp所指向的目录流中的连续条目来读取目录。
    返回的struct dirent的指针包含来与下一个目录项有关的信息。
    readdir在每次调用之后都将流转移到下一个位置上去。

    int closedir(DIR *dirp);
    close the directory stream, if it's succeed, return 0; if not, return -1 and set errno.

    void rewinddir(DIR *dirp);
    rewind the directory stream. No return value, no errno will be set.
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    struct dirent *direntp;
    DIR *dirp;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //将第一参数作为目录名，打开目录，返回目录流。
    if((dirp = opendir(argv[1])) == NULL)
    {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    //读取目录流，每次返回一项，显示该目录项
    while((direntp = readdir(dirp)) != NULL)
        printf("%s\n", direntp->d_name);
    //如果没有关闭文件并且errno被设置为EINTR（被信号打断），那就继续执行该操作。
    while((closedir(dirp) == -1) && (errno == EINTR))
        ;

    return 0;
}

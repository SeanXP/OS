/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < open.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/04/18 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>          //open()
#include <unistd.h>         //close(), unlink()
#include <sys/stat.h>
#include <errno.h>
// fopen(), fclose() - <stdio.h>

#define FILENAME    "./my.dat"
#define FILENAME2   "./newfile"

int main(int argc, char* argv[])
{
     /*
        int open(const char *path, int flags, ...);
        int open(const char *path, int flags, mode_t perms);
            path:   文件路径名
            flags:  O_RDONLY 只读, O_WRONLY 只写, O_RDWR 读写访问
                    O_APPEND 添加至文件末尾, O_TRUNC 写前清空原文件,
                    O_CREAT 创建文件，必须指定权限
                    O_CREAT | O_EXCL(文件不存在则创建文件, 已存在则返回错误)
                    O_NOCTTY 防止打开的设备变成控制终端,
                    O_NONBLOCK 不等待命名管道或特殊文件,
                    O_DSYNC/O_RSYNC/O_SYNC 设置同步I/O方式;
            perms:  permissions (when creating), S_I1222 ( 1: R/W/X, 222: USR/GRP/OTH)
                    S_IRUSR | S_IWUSR | S_IXUSR
                    S_IRGRP | S_IWGRP | S_IXGRP
                    S_IROTH | S_IWOTH | S_IXOTH
    */
    int fd;

    // read only a exist file.
    if((fd = open(FILENAME, O_RDONLY)) < 0)
    {
        perror("open failed");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // create a new file.
    // perms: rw-r--r--, 644;
    if((fd = open(FILENAME2, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("create failed");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // clear file, O_TRUNC;
    // #define cleat(path, perms) open(path, O_WRONLY | O_CREAT | O_TRUNC, perms)
    if((fd = open(FILENAME2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("clear file failed");
        exit(EXIT_FAILURE);
    }
    close(fd);

    /*
       int unlink(const char *path);
       Return 0 on success or -1 on error (sets errno)
       unlink系统调用从目录中删除文件的链接, 并将信息节点的引用链接数减1，当减到0则文件系统删除此文件;
    */
    if(unlink(FILENAME2) == -1)
    {
        perror("unlink file failed");
        exit(EXIT_FAILURE);
    }

    /*
       创建临时文件
       int mkstemp(char* template);
       Return open file descriptor or -1 on error (may not set errno)
       mkstemp绝对确保临时文件的唯一性, 需要给定一个以6个X结尾的名称模板(/tmp/temp.XXXXXX)
    */
    char pathname[] = "/tmp/temp.XXXXXX";
    errno = 0;
    if((fd = mkstemp(pathname)) == -1)
    {
        perror("mkstemp file failed");
        exit(EXIT_FAILURE);
    }
    printf("temp file: %s\n", pathname);
    if(unlink(pathname) == -1)
    {
        perror("unlink file failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

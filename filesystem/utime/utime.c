/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < utime.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/25 >
  > Description:       utime, utimes - change file last access and modification times

  #include <sys/types.h>
  #include <utime.h>

  int utime(const char *filename, const struct utimbuf *times);
  Return 0 on success, or -1 on error;
  utime()可显式改变文件的atime, mtime；解压文件时，tar(1)和unzip(1)之类的程序都会使用这些系统调用重置时间戳；
  struct utimbuf记录自Epoch以来的秒数；

  struct utimbuf {
    time_t actime;       // access time
    time_t modtime;      // modification time
  };

  若utime()的参数times为NULL，则将文件的atime/mtime都设置为当前时间；
  若utime()的参数times为指向utimbuf的指针，则设置为utimbuf的内容；调用程序要么具有特权级别（CAP_FOWNER），要么进程的EUID匹配文件的UID（仅对文件具有写权限是不够的）。

  #include <sys/time.h>
  int utimes(const char *filename, const struct timeval times[2]);
  utimes()与utime()的区别是，utimes()可以以微秒级精度来指定时间戳；

  int futimes(int fd, const struct timeval tv[2]);
  int lutimes(const char *filename, const struct timeval tv[2]);
 ****************************************************************/

#define _BSD_SOURCE     // get major() and minor() from <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    struct stat statbuf;
    struct utimbuf utb;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s pathname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 1. 通过stat()获取文件的时间戳
    //{{{
    if(stat(argv[1], &statbuf) == -1)
    {
        perror("stat() error");
        exit(EXIT_FAILURE);
    }
    printf("last access time:   %s",        ctime(&statbuf.st_atime));
    printf("\tlast modify time:   %s",        ctime(&statbuf.st_mtime));
    //printf("\t\tlast status time:   %s",        ctime(&statbuf.st_ctime));
    //}}}
    // 2. 更新时间戳
    utb.actime = statbuf.st_atime + 1;
    utb.modtime = statbuf.st_mtime + 1;
    if(utime(argv[1], &utb) == -1)
    {
        perror("utime() error");
        exit(EXIT_FAILURE);
    }
    // 3. 检查新的时间戳
    //{{{
    if(stat(argv[1], &statbuf) == -1)
    {
        perror("stat() error");
        exit(EXIT_FAILURE);
    }
    printf("last access time:   %s",        ctime(&statbuf.st_atime));
    printf("\tlast modify time:   %s",        ctime(&statbuf.st_mtime));
    //printf("\t\tlast status time:   %s",        ctime(&statbuf.st_ctime));
    //}}}

    return 0;
}

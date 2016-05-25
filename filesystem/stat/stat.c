/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < stat.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/24 >
  > Description:       获取文件状态信息 get file status

    int stat(   const char *restrict pathname,   struct stat *restrict buf);
    int lstat(  const char *restrict pathname,   struct stat *restrict buf);
    int fstat(  int fd,                          struct stat *buf);

    stat()返回命名文件的信息；
    lstat()类似stat()，不过如果为符号链接，则返回符号链接自身，而非指向的文件；
    fstat()利用打开的文件描述符来访问文件；

    成功返回0，失败返回-1并设置errno.

    restrict修饰符号说明不允许path和buf产生重叠。
    reserved为C语言中的一种类型限定符，用于告诉编译器，对象已经被指针所引用，不能通过除该指针外所有其他直接或间接的方式修改该对象的内容。

       All of these system calls return a stat structure, which contains the following fields:

           struct stat {
               dev_t     st_dev;         // ID of device containing file
               ino_t     st_ino;         // inode number
               mode_t    st_mode;        // file type and mode
               nlink_t   st_nlink;       // number of hard links
               uid_t     st_uid;         // user ID of owner
               gid_t     st_gid;         // group ID of owner
               dev_t     st_rdev;        // device ID (if special file)
               off_t     st_size;        // total size, in bytes
               blksize_t st_blksize;     // blocksize for filesystem I/O
               blkcnt_t  st_blocks;      // number of 512B blocks allocated

               // Since Linux 2.6, the kernel supports nanosecond precision for the following timestamp fields.
               // For the details before Linux 2.6, see NOTES.

               struct timespec st_atim;  // time of last access
               struct timespec st_mtim;  // time of last modification
               struct timespec st_ctim;  // time of last status change

           #define st_atime st_atim.tv_sec      // Backward compatibility
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };
 ****************************************************************/

#define _BSD_SOURCE     // get major() and minor() from <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

// 决定filePermStr()是否输出SUID/SGID信息，设置参数flags为FP_SPECIAL则输出;
#define FP_SPECIAL 1

void print_stat(struct stat *statval);

// 将文件权限掩码转换为字符串
char * filePermStr(mode_t perm, int flags);

int main(int argc, char* argv[])
{
    struct stat statbuf;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s pathname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(stat(argv[1], &statbuf) == -1)
    {
        perror("Failed to getfile status");
        exit(EXIT_FAILURE);
    }
    print_stat(&statbuf);
    return 0;
}

void print_stat(struct stat *statval)
{
    if(statval == NULL)
        return;

    // st_size: file size, st_nlink: link number
    printf("device i-node:      major=%d,minor=%d \n",  major(statval->st_dev), minor(statval->st_dev));
    printf("inode number:       %lld \n",   statval->st_ino);
    printf("permissions:        %d \t",     statval->st_mode);
        {
            int mode = statval->st_mode;
            // 也可是使用宏定义，测试宏S_ISREG()
            if((mode & S_IFMT) == S_IFREG)
                printf("regular file");
            if(S_ISDIR(mode))
                printf("directory");
            if(S_ISCHR(mode))
                printf("char device");
            if(S_ISBLK(mode))
                printf("block device");
            if(S_ISFIFO(mode))
                printf("fifo/pipe file");
            if(S_ISSOCK(mode))
                printf("socket");
            if(S_ISLNK(mode))
                printf("link file");
        }
    printf("\t %s \n", filePermStr(statval->st_mode, FP_SPECIAL));
    printf("hard link number:   %d \n",     statval->st_nlink);
    printf("UID:                %d \n",     statval->st_uid);
    printf("GID:                %d \n",     statval->st_gid);
    printf("device type:        %d \n",     statval->st_rdev);
    printf("last access time:   %s",        ctime(&statval->st_atime));
    printf("last modify time:   %s",        ctime(&statval->st_mtime));
    printf("last status time:   %s",        ctime(&statval->st_ctime));
    printf("file size:          %lld \n",   statval->st_size);
    printf("block number:       %lld \n",   statval->st_blocks);
    printf("optimal I/O size:   %d \n",     statval->st_blksize);

}

// 将文件权限掩码转换为字符串
char * filePermStr(mode_t perm, int flags)
{
#define PERM_STR_SIZE   sizeof("rwxrwxrwx")
    static char str[PERM_STR_SIZE];
    snprintf(str, PERM_STR_SIZE, "%c%c%c%c%c%c%c%c%c",
            (perm & S_IRUSR) ? 'r':'-', (perm & S_IWUSR) ? 'w':'-',
            (perm & S_IXUSR) ?
                    (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's':'x'): (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S':'-'),
            (perm & S_IRGRP) ? 'r':'-', (perm & S_IWGRP) ? 'w':'-',
            (perm & S_IXGRP) ?
                    (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's':'x'): (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S':'-'),
            (perm & S_IROTH) ? 'r':'-', (perm & S_IWOTH) ? 'w':'-',
            (perm & S_IXOTH) ?
                    (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't':'x'): (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T':'-')
            );

    return str;
}

/*************************************************************************
    > File Name: status.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 09时45分41秒
    > Last Changed: 
    > Notes: 检索文加状态信息
	>		 调用./status filename以查看
	>		 可以结合stat filename以对照 
*************************************************************************/

#include<stdio.h>
#include<time.h>
#include<sys/stat.h>

// int lstat(const char *restrict path, struct stat *restrict buf);
// 
// 
// int stat(const char *restrict path, struct stat *restrict buf);
//
//  fstat函数利用打开的文件描述符来访问文件，lstat和stat通过路径名访问.
//  lstat & stat都根据路径名访问文件，当文件为符号文件时，两者的返回才不一样。
//  成功返回0，失败返回-1并设置errno.
//  restrict修饰符号说明不允许path和buf产生重叠。
//
//  struct stat结构体成员
//  dev_t st_dev;
//  ino_t st_ino;
//  ...

int main(int argc, char *argv[])
{
	struct stat statbuf;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s file_pathname\n", argv[0]);
		return 1;
	}

	if(stat(argv[1], &statbuf) == -1)
		perror("Failed to getfile status");
	else
	{
		printf("Filename:\"%s\"\n",argv[1]);
		// st_size: file size, st_nlink: link number
		printf("Size:%ld\t",(long int)(statbuf.st_size)); 
		printf("Blocks:%ld\tBlock Size:%ld\t\n", (long int)statbuf.st_blocks, (long int)statbuf.st_blksize);
		
		printf("Device:%ld\t",(long int)(statbuf.st_dev));
		printf("Inode:%ld\t", (long int)statbuf.st_ino);
		printf("Link:%ld\t\n",(long int)statbuf.st_nlink);
		printf("UID:%ld\tGID:%ld\t\n", (long int)statbuf.st_uid, (long int)statbuf.st_gid);
		// st_mode: 文件的访问权限和文件类型
		// st_ino: inode number
		// st_atime: accessd time, st_mtime: modify time, st_ctime: change time
		printf("last accessd at %s", ctime(&statbuf.st_atime));		
		printf("last modify at %s", ctime(&statbuf.st_mtime));
		printf("last change at %s", ctime(&statbuf.st_ctime));
	}

    return 0;
}



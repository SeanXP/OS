/*************************************************************************
    > File Name: dir.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 09时26分46秒
    > Last Changed: 
    > Notes: 目录访问函数练习 
*************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<errno.h>

// DIR *opendir(const char *dirname);
// 成功则返回一个指向目录对象的指针，不成功返回空指针并设置errno.
// DIR 表一个目标流. directory stream. 特定目录中所有目录项组成的一个有序序列.
//
// struct dirent *readdir(DIR *dirp);
// 通过返回dirp所指向的目录流中的连续条目来读取目录。
// 返回的struct dirent的指针包含来与下一个目录项有关的信息。
// readdir在每次调用之后都将流转移到下一个位置上去。
//
// int closedir(DIR *dirp);
// close the directory stream, if it's succeed, return 0; if not, return -1 and set errno.
//
// void rewinddir(DIR *dirp);
// rewind the directory stream. No return value, no errno will be set.


int main(int argc, char *argv[])
{

	struct dirent *direntp;
	DIR *dirp;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
		return 1;
	}

	//将第一参数作为目录名，打开目录，返回目录流。
	if((dirp = opendir(argv[1])) == NULL)
	{ 
		perror("Failed to open directory");
		return 1;
	}

	//读取目录流，每次返回一项，显示该目录项
	while((direntp = readdir(dirp)) != NULL)
		printf("%s\n", direntp->d_name);
	//如果没有关闭文件并且errno被设置为EINTR（被信号打断），那就继续执行该操作。
	while((closedir(dirp) == -1) && (errno == EINTR))  ;

    return 0;
}


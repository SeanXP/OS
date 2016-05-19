/*************************************************************************
    > File Name: chdir.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 08时41分44秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>

// int chdir(const char *path);
// 更改当前目录，成功返回0，失败返回-1并设置errno.

// char* getcwd(char *buf, size_t size);
// 获取当前工作目录的路径名。用户给出缓存以及大小。
// 成功返回一个指向 *buf的指针，失败返回NULL并设置errno.

#define PATH_MAX 255
int main(int argc, char *argv[])
{
	char mycwd[255];

	if(argc < 2)
	{
		fprintf(stderr, "Usage: chdir [path]\n");
		return 1;
	}

	if(getcwd(mycwd, PATH_MAX) == NULL)
	{
		perror("Failed to get current working directory");
		return 1;
	}

	printf("Current working directory: %s\n", mycwd);
	
	if(chdir(argv[1]) == -1)
		perror("Failed to change current working directory");

	if(getcwd(mycwd, PATH_MAX) == NULL)
	{
		perror("Failed to get current working directory");
		return 1;
	}

	printf("Current working directory: %s\n", mycwd);

    return 0;
}


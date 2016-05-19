/*************************************************************************
    > File Name: pathconf.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 09时12分09秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// long fpathconf(int fildes, int name);
// 根据文件描述符以及极限标识符，返回极限标志符的当前值。
//
// long pathconf(const char *path, int name);
// 根据文件路径名以及极限标志符，。。。
//
// long sysconf(int name);
// 返回极限标志符的当前值


int main()
{
	long path_max;
	char *mycwdp;
	
	//查看当前路径"."的极限标志符"_PC_PATH_MAX"的值，作为路径缓冲区的大小
	if((path_max = pathconf(".", _PC_PATH_MAX)) == -1)
	{
		perror("Failed to determine to pathname length");
		return 1;
	}
	
	//malloc路径缓冲区
	if((mycwdp = (char *) malloc(path_max * sizeof(char))) == NULL)
	{
		perror("Failed to allocate space for pathname buffer");
		return 1;
	}	

	//获取当前工作路径
	if(getcwd(mycwdp, path_max) == NULL)
	{
		perror("Failed to get current working directory");
		return 1;
	}

	printf("Current working directory: %s\n", mycwdp);

    return 0;
}


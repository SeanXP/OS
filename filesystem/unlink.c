/*************************************************************************
    > File Name: unlink.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 14时10分38秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>

// int unlink(const char *path);
// 删除对应的文件项，如果对应的文件项目链接计数为0，且没有进程打开，将释放对应文件。
// 


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s filename", argv[0]);
		return 1;
	}

	if(unlink(argv[1]) == -1)
	{
		perror("Failed to unlink the file");
		return 1;
	}

    return 0;
}


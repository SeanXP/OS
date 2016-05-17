/************************************************************************
    > File Name: link.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 14时00分38秒
    > Last Changed: 
    > Notes:文件硬链接以及符号链接函数联系 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>

// int link(const char *path1, const chat *path2);
// 成功返回0，失败返回-1并设置errno.
//
// int unlink(const char *path);
// 删除指定的文件项，如果文件对应的inode连接数目为0，且没有进程打开该文件，则释放该文件。
// 成功返回0，失败返回-1并设置errno.

int main(int argc, char *argv[]) 
{
	
	if(argc != 3)
	{
		fprintf(stderr, "Usage:%s source_file link_file\n", argv[0]);
		return 1;
	}
	
	if(link(argv[1],argv[2]) == -1)
	{
		perror("Failed to make a new link");
		return 1;
	}

    return 0;
}


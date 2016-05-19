/*************************************************************************
    > File Name: symlink.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 14时15分52秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>

// int symlink(const char *path1, const char *path2);
// 为paht1文件建立一个符号链接，将占用一个inode和一个block
// 用来指向对应的硬文件。

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s source_file symlink_file\n", argv[0]);
		return 1;
	}

	if(symlink(argv[1], argv[2]) == -1)
	{
		perror("Failed to create a new symlink");
		return 1;
	}

    return 0;
}


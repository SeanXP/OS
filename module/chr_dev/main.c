/*************************************************************************
    > File Name: main.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月27日 星期三 20时36分34秒
    > Last Changed: 
    > Notes:	测试chr_dev字符驱动的主程序 
*************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define CHR_DEV_NAME	"/dev/chr_dev" //自己创建的字符驱动设备节点
#define BUFFER_NUM		32
int main()
{
	int ret;
	char buf[BUFFER_NUM];

	int fd = open(CHR_DEV_NAME, O_RDONLY | O_NDELAY);	//像普通文件一样打开字符设备

	if(fd < 0)	// fail to open
	{
		printf("Open file %s failed!\n", CHR_DEV_NAME);
		return -1;
	}

	read(fd, buf, 32);

	close(fd);

    return 0;
}


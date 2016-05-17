/*************************************************************************
    > File Name: main.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月27日 星期三 20时36分34秒
    > Last Changed: 
    > Notes:	测试chr_dev字符驱动的主程序 
	>			Usage: main write
	>				   main read
*************************************************************************/

#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define CHR_DEV_NAME	"/dev/char_dev" //自己创建的字符驱动设备节点
#define	BUFFER_SIZE		1024
char buffer[BUFFER_SIZE];

int write_chr(const char *string);
int read_chr();

int main(int argc, char *argv[])
{
	if((argc == 3) && (strcmp(argv[1],"write") == 0))
	{
		write_chr(argv[2]);
	}
	else if((argc == 2) && (strcmp(argv[1], "read") == 0))
	{
		read_chr();
	}
	else
	{
		fprintf(stderr, "Usage: %s write some_strings\nUsage: %s read\n", argv[0], argv[0]);
		return -1;
	}

    return 0;
}

int write_chr(const char *string)
{
	int fd = open(CHR_DEV_NAME, O_RDWR | O_NDELAY);	//这里要对设备文件进行读写，必须要有相应的权限	
	//O_NDELAY & O_NONBLOCK都使I/O变得非搁置模式,在读取不到数据或写入缓冲区已满会
	//马上返回，不会搁置程序动作。
		
	if(fd < 0)
	{
		fprintf(stderr, "Failed to open file %s!\n", CHR_DEV_NAME);
		return -1;
	}
	if(write(fd,string,strlen(string)) == -1)
	{
		fprintf(stderr, "Failed to write into file %s!\n", CHR_DEV_NAME);
		return -1;
	}
	printf("write into file %s !\n", CHR_DEV_NAME);

	close(fd);

	return 0;
}


int read_chr()
{
	int fd = open(CHR_DEV_NAME, O_RDONLY | O_NDELAY);	
	//O_NDELAY & O_NONBLOCK都使I/O变得非搁置模式,在读取不到数据或写入缓冲区已满会
	//马上返回，不会搁置程序动作。
		
	if(fd < 0)
	{
		fprintf(stderr, "Failed to open file %s!\n", CHR_DEV_NAME);
		return -1;
	}
	if(read(fd,buffer,BUFFER_SIZE) == -1)
	{
		fprintf(stderr, "Failed to write into file %s!\n", CHR_DEV_NAME);
		return -1;
	}
	printf("read file %s :\n", CHR_DEV_NAME);
	printf("%s\n",buffer);

	close(fd);
	return 0;
}

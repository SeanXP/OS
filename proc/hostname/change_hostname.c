/*************************************************************************
    > File Name: change_hostname.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月30日 星期六 21时32分34秒
    > Last Changed: 
    > Notes:	显示/proc/sys/kernel/hostname 
	>			修改hostname
	>			再次显示hostname
	>			可以再开一个bash shell查看当前的hostname.
	> Usage:	change_hostname new_hostname;
*************************************************************************/

#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char buffer[100];

	//检查参数
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s new_hostname\n", argv[0]);
		return -1;
	}

	printf("\nOpen /proc/sys/kernel/hostname...\n");
	//打开文件, "r+",可读写,文件必须存在
	if((fp = fopen("/proc/sys/kernel/hostname","r+")) == NULL)
	{
		fprintf(stderr, "Error: Failed to open /proc/sys/kernel/hostname. \n");
		return -1;
	}
	//读取文件
	if(fgets(buffer,80,fp) == NULL)
	{
		fprintf(stderr, "Error: Failed to read the file. \n");
		return -1;
	}

	printf("Hostname is : %s\n", buffer);

	//回到文件开头
	fseek(fp, 0, SEEK_SET);
	
	//将新的hostname写入文件
	strcpy(buffer,(const char *) argv[1]);
	printf("\nWrite new hostname to /proc/sys/kernel/hostname...\n");
	if(fputs(buffer, fp) == EOF)
	{
		fprintf(stderr, "Error: Failed to write to file. \n");
		return -1;
	}

	fseek(fp, 0, SEEK_SET);
	
	if(fgets(buffer,80,fp) == NULL)
	{
		fprintf(stderr, "Error: Failed to read the file. \n");
		return -1;
	}

	printf("OK, Now, The Hostname is : %s\n", buffer);
	printf("Open a new bash shell and Let's see the hostname!\n");

	fclose(fp);

    return 0;
}


/*************************************************************************
    > File Name: which.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月08日 星期五 14时33分02秒
    > Last Changed: 
    > Notes:实现which功能，查找可执行文件的全程路径名
	>		1.如果参数包括路径说明符，那which程序检查是否含有该可执行文件
	>		2.如果参数不包括路径，那进行查找并显示
	>		如果查找成功，返回绝对路径
	>		如果查找失败，程序结束
	>		程序的行为与Linux 中的which完全相同
	>		支持多参数
*************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>



#define PATH_BUF_NUM 100

int main(int argc, char *argv[])
{
	int i = 1;
	char path_buf[PATH_BUF_NUM]; //存储环境变量PATH路径
	struct stat statbuf;

	if(argc == 1) //没有参数，则不进行程序，返回
		return 0;
	for(i = 1; i < argc; i++) // 没一个参数，都执行一遍查找
	{
		//1.判断参数是否含有路径
		if(argv[i][0] == '/') //含路径，则直接判断路径中是否含有该二进制文件。
		{
			int len = strlen(argv[i]) - 1; //定位路径的最后一个字符
			int j = len;				 //用作目录与文件的分割符
			for(;argv[i][j] != '/';j--); //定位目录argv[i][0] - argv[i][j], 文件名argv[i][j+1] - 
			if(j == len) //纯目录判断，如果最后一个字符都是'/'，那么为纯目录，没有必要再执行命令
			{
				fprintf(stderr, "There is no file need to find.\n");
				continue;
			}
			strncpy(path_buf, argv[i], j+1);
			path_buf[j+1] = '\0'; 

			//进入目录
			if(chdir(path_buf) == -1) //目录错误
			{
				fprintf(stderr, "The directory is wrong.\n");
				continue;	
			}
			else //目录正确，开始验证文件
			{
				if(stat(argv[i], &statbuf) == -1) //打开文件失败，不存在文件
				{
					fprintf(stderr, "The file is not exist in this directory.\n");
					continue;
				}
				else //存在文件，则开始验证是否为普通文件
				{
					if(S_ISREG(statbuf.st_mode) == 0) //不是普通文件
					{
						fprintf(stderr, "The filetype is wrong.\n");
						continue;
					}
					//普通文件，则查看文件是否有可执行权限
					////////////////不知道如何查看文件权限，暂且搁置
				/*	if((S_IXUSR(statbuf.st_mode) || S_IXGRP(statbuf.st_mode) || S_IXOTH(statbuf.st_mode)) == 0)
					{
						//没有可执行权限
						fprintf(stderr, "The file is not a bin file.\n");
						continue;
					}
					*/
				}
			}

		}	
		else				//不含路径，则先从环境变量中查找PATH路径。
		{
			printf(" \n");
		}
	}

    return 0;
}


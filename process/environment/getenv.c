/*************************************************************************
    > File Name: getenv.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月06日 星期三 16时26分23秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>
#include<stdlib.h>

// char *getenv(const char *name);
// 读取参数name对应的环境变量的值，如果没有则返回NULL;
//
int main(int argc, char **argv)
{
	int i;

	for(i = 1; i < argc; i++)
	{
		printf("[%s] : %s\n", argv[i], getenv(argv[i]));
	}
    return 0;
}


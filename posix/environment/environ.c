/*************************************************************************
    > File Name: environ.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月06日 星期三 16时20分45秒
    > Last Changed: 
    > Notes: 进程开始执行的时候，外部变量environ指向进程环境列表。 
*************************************************************************/

#include<stdio.h>

extern char **environ;

int main()
{
	int i;

	printf("The environment list follows:\n");
	for(i = 0;environ[i] != NULL; i++)
		printf("environ[%d]: %s\n", i, environ[i]);

    return 0;
}


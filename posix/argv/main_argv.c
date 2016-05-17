/*************************************************************************
    > File Name: main_argv.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月06日 星期三 16时05分33秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	for(i = 0; i < argc; i++)
	{
		printf("%s\n",argv[i]);
	}
    return 0;
}


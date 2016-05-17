/*************************************************************************
    > File Name: test.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月16日 星期六 20时20分10秒
    > Last Changed: 
    > Notes: 系统调用函数测试 
*************************************************************************/

#include<stdio.h>

int main()
{
	int xh = 0;

	printf("请输入你的学号:\n");
	while((scanf("%d", &xh)) == 1)
	{
		printf("%d\n", syscall(349, xh));
	}
	
	syscall(350);
    return 0;
}



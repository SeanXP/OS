/*************************************************************************
    > File Name: test.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月16日 星期六 20时20分10秒
    > Last Changed: 
    > Notes: 系统调用函数测试 
*************************************************************************/

#include<stdio.h>

int xuehao(int xuehao)
{
	if(xuehao % 2 == 1)	//参数为奇数，则返回最后5位
		return (xuehao % 100000);
	else				//参数为偶数,则返回最后4位
		return (xuehao % 10000);
}

int main()
{
	int xh = 0;

	printf("请输入你的学号:\n");
	while((scanf("%d", &xh)) == 1)
	{
		printf("%d\n", xuehao(xh));
	}

    return 0;
}



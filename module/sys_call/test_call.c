/*************************************************************************
    > File Name: test_call.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月24日 星期日 00时48分26秒
    > Last Changed: 
    > Notes: 用来测试是否成功将系统调用添加到内核中去.
*************************************************************************/

#include<stdio.h>

int main()
{
	long pid = 0;
	pid = syscall(223);
	printf("%ld\n", pid);

    return 0;
}


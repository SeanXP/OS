/*************************************************************************
    > File Name: fork_chain.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月06日 星期三 17时19分39秒
    > Last Changed: 
    > Notes:利用fork函数产生的进程链。
	>		循环n次，每次都调用fork()，对于子进程，返回为0，执行条件语句退出。
	>		对于父进程，返回不为0，不执行条件语句，故仍为下一次循环的父进程。
	>		链的数目由主函数参数确定. 
	>		Usage: ./a.out 10
*************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char **argv)
{
	pid_t childpid = 0;
	int i, n;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s processes\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);

	for(i = 1; i < n; i++)
		if((childpid = fork()) <= 0) ////			This is different with fork_chain.c
			break;


	// 默认情况下，系统对写入stdout的输出进行缓冲，可能不会在printf返回之后立即出现。
	// 而写入stderr的消息不会被缓冲
	// 因此，对于调试消息应该使用stderr.
	fprintf(stderr, "i:%d PID:%d PPID:%d child PID:%d \n", i, getpid(), getppid(), childpid);

    return 0;
}


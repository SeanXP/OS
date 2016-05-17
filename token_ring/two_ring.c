/*************************************************************************
    > File Name: two_ring.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月16日 星期六 22时25分51秒
    > Last Changed: 
    > Notes:	两个进程通过两个管道连接起来 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
	int fd[2];
	pid_t child;

	pipe(fd);
	dup2(fd[0],STDIN_FILENO);
	dup2(fd[1],STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	//形成单环，stdout->stdin

	pipe(fd);		//注意现在创建的是另一个通道
	child = fork();

	if(child > 0)
		dup2(fd[1], STDOUT_FILENO);
	else if(child == 0)
		dup2(fd[0], STDIN_FILENO);
	else
		;

	close(fd[0]);
	close(fd[1]);
	//形成双环
	
	{
		int i, myint;
		for(i = 0; i < 10; i++)
		{
			write(STDOUT_FILENO, &i, sizeof(i));
			read(STDIN_FILENO, &myint, sizeof(myint));
			fprintf(stderr, "read %d from stdin by [PID:%ld]\n", myint, (long)getpid());
		}
	}


    return 0;
}


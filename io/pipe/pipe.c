/*************************************************************************
    > File Name: pipe.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月10日 星期日 15时08分52秒
    > Last Changed: 2013/11/16 
    > Notes: 管道操作练习 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

#define BUFFER_SIZE	100	//不可太小, 太小则一次读取不完发送的数据.
//发送/接收缓冲区太小, 则要利用好read/write的返回值, 实现多次发送, 
//通知也要注意后面几次发送&接收的缓存地址.

// int pipe(int fildes[2]);
// 创建一个管道，写入fildes[1]的数据可以被fildes[0]读出。
// 创建成功返回0，失败返回-1并设置errno.

int main()
{
	char buf_in[BUFFER_SIZE] = "empty";
	char buf_out[] = "Hello World by Shawn Guo";
	int bytesin;

	pid_t childpid;
	int fd[2];

	printf("open a pipe by pipe();\n");
	if(pipe(fd) == -1) 
	{
		perror("Failed to create a new pipe");
		return -1;
	}
	printf("fd[0]:%d, fd[1]:%d\n", fd[0],fd[1]);

	bytesin = strlen(buf_in);
	if((childpid = fork()) == -1)
	{
		perror("Failed to create a new process");
		return -1;
	}
	else if(childpid > 0)
	{
		// father process
		// 向fd[1]发送buf_out.
		close(fd[0]);
		printf("parent process send %lu bytes (%s)\n", strlen(buf_out), buf_out);
		write(fd[1], buf_out, strlen(buf_out));

	}
	else	//child process read fd[0].
	{
		close(fd[1]);
		bytesin = read(fd[0], buf_in, BUFFER_SIZE);
		//bytesin = read(fd[0], buf_in+bytesin, BUFFER_SIZE);	//BUFFER_SIZE太小时, 需要考虑多次接收
	}

	fprintf(stderr, "[PID:%ld,PPID:%ld]:my bufin is {%s}, my bufout is {%s}\n",
			(long) getpid(), (long)getppid(), buf_in, buf_out);
    return 0;
}


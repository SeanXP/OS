/*************************************************************************
    > File Name: n_ring.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月17日 星期日 15时58分54秒
    > Last Changed: 
    > Notes: 借助通道，创建n个进程环. n作为运行时参数传递给程序. 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

// 多进程环的创建算法
// 1. 得到单环进程
// 2. 创建另一通道，此通道将和子进程共享
// 3. fork子进程
// 4. 将子进程的输入切换成共享通道的出口fd[0]
// 5. 将父进程的输出切换到共享通道的入口fd[1]
// 6. 则建立了由父进程指向通道，由通道指向子进程，由子进程返回回去的环路
//

#define	BUFFER_SIZE	 50

void prtastr(const char *s, int fd, int n);
void waste_some_time(int n);

int delay_time = 0; //延时单位时间，默认为0.

int main(int argc, char *argv[])
{
	int fd[2];
	pid_t child;
	int process_number = 0;
	int error, i;
	char buffer[BUFFER_SIZE];
	int next_id = 0;

	//检查命令行参数是否正确
	if((argc < 2) || ((process_number = atoi(argv[1])) < 0)) 
	{
		fprintf(stderr, "Usage: %s process_number [delay_time].\n", argv[0]);
		return -1;
	}
	if(argc == 3)
	{
		if((delay_time = atoi(argv[2])) < 0)
		{
			fprintf(stderr, "Failed to get the delay time.\n");
			return -1;
		}
	}
	
	if(pipe(fd) == -1)
	{
		perror("Failed to create staring pipe");
		return -1;
	}

	if((dup2(fd[0], STDIN_FILENO) == -1) || (dup2(fd[1], STDOUT_FILENO) == -1))
	{
		perror("Failed to connect pipe by using dup2 command");
		return -1;
	}

	if((close(fd[0]) == -1) || (close(fd[1]) == -1))
	{
		perror("Failed to close extra descriptors");
		return -1;
	}
	//now, this is one-ring.
	


	
	for(i = 1; i < process_number; i++) //循环环算法
	{
		//1. 创建要和子进程共享的通道
		if(pipe(fd) == -1)
		{
			fprintf(stderr, "[%ld]:Failed to create pipe %d: %s\n",
					(long)getpid(), i, (char *)strerror(errno));
			return -1;
		}
		//2. fork子进程
		if((child = fork()) == -1)
		{
			fprintf(stderr, "[%ld]:Failed to fork a child process %d: %s.\n", 
					(long)getpid(), i, (char *)strerror(errno));
			return -1;
		}
		else if(child > 0) // parent process
			//父进程配置其输出STDOUT指向管道即可
			errno = dup2(fd[1], STDOUT_FILENO);
		else  // child process
			//子进程配置其输入STDIN来自管道
			errno = dup2(fd[0], STDIN_FILENO);

		if(errno == -1)
		{
			fprintf(stderr, "[%ld]:Failed to dup pipes for iteration %d: %s\n",
					(long)getpid(), i, (char *)strerror(errno));
			return -1;
		}

		if((close(fd[0]) == -1) || (close(fd[1]) == -1))
		{
			fprintf(stderr, "[%ld]:Failed to close extra descriptors %d: %s\n",
					(long)getpid(), i, (char *)strerror(errno));
			return -1;
		}

		//父进程配置完成，直接break跳出循环。
		//子进程需要再执行算法，和下一个进程成环
		if(child > 0) 
			break;
	}
	buffer[0] = getpid();
	next_id = child;
	for(i = 1; i < process_number);

	wait(); //这句语句相当有用，避免了孤儿进程.

	fprintf(stderr, "This is process %d . [PID:%ld\tPPID:%ld]\n",
			i, (long)getpid(), (long)getppid());

//	waitpid(child); //这句语句不能避免孤儿进程的产生.

    return 0;
}

//调用write想文件描述符fd打印字符串s,一次打印一个字符.
//输出所有字符以后，prtastr调用一个延时程序

void prtastr(const char *s, int fd, int n)
{
	int i = 0;
	for(; i < n; i++)
		write(fd, &s[i], 1);

	waste_some_time(delay_time);
}

// 延时程序, volatile防止for循环被优化.
void waste_some_time(int n)
{
	static volatile int dummy = 0;
	int i;

	for(i = 0; i < n; i++)
		dummy++;
}

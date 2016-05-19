/****************************************************************
    Copyright (C) 2014 Sean Guo. All rights reserved.
					      									  
    > File Name:         < daemonize.c >
    > Author:            < Sean Guo >
    > Mail:              < iseanxp+code@gmail.com >
    > Created Time:      < 2014/06/26 >
    > Last Changed: 
    > Description:		守护进程的编程实现

	守护进程（Daemon）是运行在后台的一种特殊进程。 它独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件。
	守护进程是一种很有用的进程。Linux的大多数服务器就是用守护进程实现的。 比如，Internet服务器inetd，Web服务器httpd等。
	同时，守护进程完成许多系统任务。比如，作业规划进程crond，打印进程lpd等。 
	守护进程的编程本身并不复杂，复杂的是各种版本的Unix的实现机制不尽相同， 造成不同Unix环境下守护进程的编程规则并不一致。

	.进程
    	.每个进程都有一个父进程
	    .当子进程终止时，父进程会得到通知并能取得子进程的退出状态。
	.进程组
	    .每个进程也属于一个进程组
		.每个进程主都有一个进程组号，该号等于该进程组组长的PID号
		.一个进程只能为它自己或子进程设置进程组ID号
	.会话期
	    .对话期(session)是一个或多个进程组的集合。
		.setsid()函数可以建立一个对话期：
		如果，调用setsid的进程不是一个进程组的组长，此函数创建一个新的会话期。
		(1)此进程变成该对话期的首进程
		(2)此进程变成一个新进程组的组长进程。
		(3)此进程没有控制终端，如果在调用setsid前，该进程有控制终端，那么与该终端的联系被解除。
		如果该进程是一个进程组的组长，此函数返回错误。
		(4)为了保证这一点，我们先调用fork()然后exit()，此时只有子进程在运行，
		子进程继承了父进程的进程组ID，但是进程PID却是新分配的，所以不可能是新会话的进程组的PID。 从而保证了这一点。


	1.守护进程的特性(后台运行,与其运行前的环境隔离开来,启动方式[1.启动脚本/etc/rc.d,   2.作业规划进程crond, 3.用户终端shell])
	2.编程要点
		2.1 后台运行, fork出进程, 结束父进程, 子进程在后台运行Daemon.
		2.2 脱离当前环境(控制终端,登录会话,进程组,文件描述符,当前目录,信号处理函数....), 这样Daemon就不受这些环境的影响.
			脱离父进程所处的登录会话与其对应的进程组, 通过setsid()使其成为新会话的领头进程.
			禁止在新会话中开启控制终端, 可再fork出子进程实现daemon.	
			关闭继承的文件描述符, 防止资源浪费或文件系统无法卸载某目录.
			更改当前目录, 防止无法卸载当前目录。
			重设文件创建掩模
		   	处理SIGCHLD信号，避免daemon产生僵尸子进程.


	说明：在系统调用库中有一个库函数可以直接使一个进程变成守护进程，
	#include <unistd.h>
	int daemon(int nochdir, int noclose);

****************************************************************/

#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h> 
#include <signal.h> 
#include <sys/param.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <time.h>

//初始化daemon.
void Daemon_Init(void)
{
	int pid; 
	
	pid = fork();
	if(pid < 0) // 创建子进程失败
	{
		printf("error: failed in fork()\n");
		exit(1);
	}
	else if(pid > 0) // The parent process
		exit(0); //结束父进程, 使得daemon进程脱离当前父进程.
	else	//pid == 0, the children process.
	{
		//父进程已结束, 脱离父进程.
		//脱离当前登录会话与进程组, 成为新会话的领头进程组长.	

		//pid_t setsid(); setsid()会创建一个新的会话，并将调用该函数的进程设置为新会话的LEADER
		//将进程和它当前的登录会话和进程组分离开,并且把它设置成一个新的对话过程的领头进程。
		//会话session是一个或多个进程组的集合。session的领头进程被杀死后, 其中的所有进程都将被杀死.
		setsid();

		//新会话可以再次打开控制终端, 而这里作为daemon进程, 需要禁止
		//通过fork子进程, 子进程不再是新会话的LEADER, 则不会打开控制终端.
		pid = fork();
		if(pid < 0) //创建子进程失败
		{
			printf("error: failed in fork()\n");
			exit(1);
		}
		else if( pid > 0 ) // parent process
			exit(0);
		else	//新会话中的子进程, 不是会话的LEADER, 运行daemon服务.
		{
			int i;
			//关闭文件描述符
			for( i = 0; i < NOFILE; ++i) //关闭所有打开的文件描述符, 防止浪费资源
				close(i);
			//更爱当前工作目录
			chdir("/tmp");
			//重设文件创建掩模
			umask(0);
		}

	}
	return; 
}	

int main()
{

	FILE *fp; 
	time_t t; 

	Daemon_Init();	//创建出一个Daemon进程, 此进程将返回, 并执行下面的任务. 

	while(1)//每隔一分钟向test.log报告运行状态 
	{ 
		sleep(60);//睡眠一分钟 
		if((fp=fopen("test_daemon.log","a")) >=0) 
		{ 
			t=time(0); 
			fprintf(fp,"I'm here at %s\n",asctime(localtime(&t)) ); 
			fclose(fp); 
		} 
	} 
	
	return 0;
}

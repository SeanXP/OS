/*************************************************************************
    > File Name: peterson.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月09日 星期六 13时20分21秒
    > Last Changed: 
    > Notes: 实现Peterson进程通信-临界区互斥算法。
	>		 模拟两个线程相互进入临界区的调度算法。
	>		 不用两个进程而用线程的原因，是因为fork创建子进程，将产生
	>		 两个地址空间，两个turn，两个interested[],不是题目的本意。
*************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define FALSE 0
#define	TRUE  1
#define	PROCESS_NUM 2				// 进程数量

int turn;							//表示现在轮到哪个进程了
int interested[PROCESS_NUM];		//初始化为FALSE;为TRUE表明对应进程想要进入临界区
int counter = 0;						//计数器

void Enter_Region(int process)      //保证进程可以安全进入临界区
{
	int other = 1 - process;		//由于只有两个进程，所以直接计算出另一个进程的号码

	interested[process] = TRUE;		//声明要进入临界区
	turn = process;					//设置标志位
	while(turn == process && interested[other] == TRUE); // 其他进程也要进入临界区时
														 // turn == process保证一个进程会循环的等待
														 //	另一个进程跳出等待，执行命令。
	//执行到这一步，说明已经进入临界区
}

void Leave_region(int process)       //调用此函数离开临界区
{
	interested[process] = FALSE;     //表示不想进入临界区
}

void *Thread_function0(void *arg) //线程0
{
	while(1) //模拟线程0，随机时间申请临界区，占用随机时间并释放
	{
		Enter_Region(0); //准备进入临界区

		//执行到这一步，说明已经进入临界区，另一个进程肯定阻塞在Enter_Region中了。
	
		//执行临界区的操作...这里仅为模拟
		printf("%3d:Thread 0 is in Critical Region now.\t\t0\n", ++counter);
		sleep((rand() % 10)); //随机延时以模拟在临界区的操作
		//临界区操作执行完毕，准备退出临界区
		Leave_region(0);
		sleep((rand() % 20)); //随机延时以模拟一段时间后再次申请临界区
	}
}

void *Thread_function1(void *arg) //线程1
{
	while(1) //模拟线程1，随机时间申请临界区，占用随机时间并释放
	{
		Enter_Region(1); //准备进入临界区

		//执行到这一步，说明已经进入临界区，另一个进程肯定阻塞在Enter_Region中了。
	
		//执行临界区的操作...这里仅为模拟
		printf("%3d:Thread 1 is in Critical Region now.\t\t1\n", ++counter);
		sleep((rand() % 10)); //随机延时以模拟在临界区的操作
		//临界区操作执行完毕，准备退出临界区
		Leave_region(1);
		sleep((rand() % 20)); //随机延时以模拟一段时间后再次申请临界区
	}
}

int main()
{
	pthread_t thread1;

	if(pthread_create(&thread1, NULL, Thread_function1, NULL)) //线程1
	{
		fprintf(stderr, "Failed to create a new thread.\n");
		return 1;
	}

	//原主线程现在为线程0
	(*Thread_function0)(NULL);

    return 0;
}


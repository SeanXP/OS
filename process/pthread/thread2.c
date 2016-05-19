/*************************************************************************
    > File Name: thread1.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月09日 星期六 10时42分16秒
    > Last Changed: 
    > Notes: 线程练习 
*************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int myglobal = 0;

void *thread_function(void *arg)
{
	int i, j;
	for(i = 0; i < 20; i++)
	{
		j = myglobal;
		j++;
		printf(".");
		fflush(stdout);
		sleep(1);
		myglobal = j;
	}
	return NULL;
}


int main(void)
{
	pthread_t mythread;
	int i = 0; 

	if(pthread_create( &mythread, NULL, thread_function,NULL)) //主线程一分为2
	{
		printf("Error creating thread.\n");
		abort();
	}

	//
	//刚开始，线程1打印一个"o"，叠加myglobal,然后睡眠，此时切换到线程2
	//线程2读取线程1刚叠加的数字，局部变量叠加，打印"."，然后睡眠，此时又切换线程1
	//线程1打印，叠加myglobal,睡眠再切换线程2
	//线程二从sleep(1)的下一句开始执行，将上一次叠加的局部变量j赋值给myglobal
	//注意，上一次叠加的结果，和这一次线程1叠加的结果相同，因此这句话没有更改myglobal的值
	//即，线程2的程序并没有更改线程1在myglobal的值。
	//
	//这就是线程间共享空间的使用。一定要时序流程。
	
	for(i = 0; i < 20; i++)
	{
		myglobal = myglobal + 1;
		printf("o");
		fflush(stdout);
		sleep(1);
	}


	if(pthread_join(mythread, NULL))
	{
		printf("Error joining thread.\n");
		abort();
	}
	
	printf("\nmyglobal equals %d\n", myglobal);

    return 0;
}


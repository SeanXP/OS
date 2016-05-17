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

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//				      void *(*start_routine)(void *), void *arg);
// Compile and link with -pthread "eg. gcc thread.c -o thread -lpthread"


void *thread_function(void *arf)
{
	int i;
	for(i = 0; i < 20; i++)
	{
		printf("Thread says hi!\n");
		sleep(1);
	}
	return NULL;
}


int main(void)
{
	pthread_t mythread;

	if(pthread_create( &mythread, NULL, thread_function,NULL))
	{
		printf("Error creating thread.\n");
		abort();
	}

	if(pthread_join(mythread, NULL))
	{
		printf("Error joining thread.\n");
		abort();
	}

    return 0;
}


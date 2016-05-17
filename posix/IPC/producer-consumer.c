/*************************************************************************
    > File Name: producer-consumer.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月09日 星期六 14时35分59秒
    > Last Changed: 
    > Notes:	【生产者-消费者问题】	线程代码实现 
*************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define	MAX_NUM 10		//需要生产的数量

pthread_mutex_t the_mutex;		//声明线程用的互斥量
pthread_cond_t condc, condp;	//声明线程用的条件变量

int buffer = 0;					//生产者消费者使用的缓冲区,这里只有一个缓冲区，0为空，1为满。

void *Producer(void *arg)
{
	int i;
	
	for(i = 1; i <= MAX_NUM; i++)
	{
		pthread_mutex_lock(&the_mutex); //打算使用临界区，尝试加锁
		//加锁成功将直接运行下一步，失败将阻塞
		printf("Producer is in buffer.\n");
		while(buffer != 0)				//缓冲区满，则利用条件变量阻塞自己，直到消费者取出数据
			//条件变量经常和互斥量一起使用，此函数先解除互斥量的锁，再挂起线程等待条件变量符合条件
			//等到相应的信号后，再重新给互斥量加锁。
		{
			printf("Buffer is Full. So producer sleep...\n");
			pthread_cond_wait(&condp, &the_mutex);	
			printf("Producer wake up by consumer.\n");
		}
		buffer = i;						//将数据放入缓冲区
		printf("Producer set the buffer. Now Let's wake up the consumer.\n");
		pthread_cond_signal(&condc);	//给condc发送信号，唤醒消费者
		pthread_mutex_unlock(&the_mutex);	//解锁，释放缓冲区，此时消费者可以在缓冲区操作了
		sleep(1); //信号量发送不够快，如果不延时，往往还会在跑一边循环，然后阻塞住,可以注释此行以做比较
	}
	pthread_exit(0);
}

void *Consumer(void *arg)
{
	int i;
	for(i = 1; i <= MAX_NUM; i++)
	{
		pthread_mutex_lock(&the_mutex);
		printf("Consumer is in buffer.\n");
		while(buffer == 0)				//当缓冲区为空，则利用条件变量挂起进程，等待信号
		{
			printf("Buffer is EMPTY. So consumer sleep...\n");
			pthread_cond_wait(&condc, &the_mutex);
			printf("Consumer wake up by Producer.\n");
		}
		printf("Consumer fetch %d. Now Let's wake up the producer.\n", buffer);//取出数据
		buffer = 0;
		pthread_cond_signal(&condp);	//唤醒生产者
		pthread_mutex_unlock(&the_mutex);
		sleep(1);
	}
	pthread_exit(0);
}

int main()
{
	pthread_t thread0, thread1;

	if(pthread_create(&thread0, NULL, Producer, NULL))
	{
		fprintf(stderr, "Failed to create a new thread for producer.\n");
		return 1;
	}
	(*Consumer)(NULL);

    return 0;
}


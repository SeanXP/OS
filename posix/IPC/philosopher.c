/*************************************************************************
    > File Name: philosopher.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月09日 星期六 15时49分03秒
    > Last Changed: 
    > Notes:	【哲学家就餐问题】  代码实现
	>			 Usage: ./a.out thinktime eattime
	>			 不带参数则使用默认值，10 20
*************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define	PEOPLE_NUM		5									  //哲学家人数
#define	LEFT(i)			(((i) + PEOPLE_NUM - 1) % PEOPLE_NUM) //左邻居编号
#define	RIGHT(i)		(((i) + 1) % PEOPLE_NUM)		      //右邻居编号
#define	THINKING		0		//哲学家的三种状态
#define	HUNGRY			1
#define	EATING			2

int THINKING_TIME = 10;		//思考最大时间
int EATING_TIME = 20;		//吃饭最大时间

int state[PEOPLE_NUM];		//记录每位哲学家的状态
pthread_mutex_t mutex;	//临界区的互斥
pthread_mutex_t s[PEOPLE_NUM];		//每个哲学家一个信号量。	信号量与互斥量结合使用
							//当线程加锁互斥量成功，但是对临界区的结果不满意时
							//使用信号量加锁，同时释放互斥量，直到接受到满意的信号
							//再继续执行临界区加锁操作

void test(int i)				//哲学家i尝试拿起两个叉子
{
	if((state[i] == HUNGRY) && (state[LEFT(i)] != EATING) && (state[RIGHT(i)] != EATING))
	{

		//如果饿了，而且左边和右边都没有吃，那么就开吃！
		state[i] = EATING;
		pthread_mutex_unlock(&s[i]);
		printf("Ph.%d get forks! Eating.......\n", i);
	}
	else if((state[i] == HUNGRY))
	{
		printf("Ph.%d can't find forks! Maybe %d or %d took the fork.\n", i, LEFT(i), RIGHT(i));
	}
	else // state[i] != HUNGRY
	{
	}
}

void take_forks(int i)	// 参数为哲学家编号
{
//第i个哲学家尝试取叉子的操作，执行成功，则可以开始吃饭
//否则，将阻塞

	pthread_mutex_lock(&mutex);		//进入临界区，尝试加锁

	state[i] = HUNGRY;				//设置状态，想吃饭
	printf("Ph.%d try take forks...\n", i);
	test(i);						//尝试获得两把叉子，成功则进入EATING状态，且信号量设置
									//失败，线程将阻塞在下一句信号量操作中，等待信号。

	pthread_mutex_unlock(&mutex);	//离开临界区
	pthread_mutex_lock(&s[i]);	
	//信号量的操作，如果得到叉子，那么已经pthread_mutex_unlock过，则现在pthread_mutex_lock回复正常
	//如果没有得到叉子，那么pthread_mutex_lock会导致线程阻塞，等待信号量。
}

void put_forks(int i)
{
	pthread_mutex_lock(&mutex);
	
	printf("Ph.%d is full! Put forks.\n", i);
	state[i] = THINKING;	//哲学家吃饱的节奏~

	test(LEFT(i));			//吃饱则放下叉子，检测左右二位有没有饿着
	test(RIGHT(i));			//如果有饿着的，发个信号，告诉他，你这边有叉子来
							//当然饿着的那位将跳出阻塞，重新开始尝试拿叉子
							//但是能不能吃，还要看饿着的人的另外一位是否空闲了叉子
							//饿着的人好痛苦有木有!

	pthread_mutex_unlock(&mutex);				//离开临界区
}


void think()		// 思考随机时间
{
	sleep((rand() % THINKING_TIME));
}

void *philosopher(void *arg) //每个线程要执行的程序, 参数为一个int指针，表示编号
{
	int i = *((int *)arg);

	while(1)
	{
		printf("Ph.%d is thinking...\n", i);
		think();		//哲学家在思考
		printf("Ph.%d feel hungry now\n", i);
		take_forks(i);
		//执行到这一步，说明哲学家已经开始吃了..
		sleep((rand() % EATING_TIME));
		put_forks(i);	//吃饱后放下叉子,并通知一下左右二位
	}
}

int main(int argc, char *argv[])
{
	pthread_t	thread[PEOPLE_NUM];
	int i;
	int id[PEOPLE_NUM];

	if(argc == 3) //3个参数，则配置参数，否则，使用默认值
	{
		THINKING_TIME = atoi(argv[1]);
		EATING_TIME   = atoi(argv[2]);
	}

	for(i = 0; i < PEOPLE_NUM; i++)
		id[i] = i;

	for(i = 0; i < PEOPLE_NUM; i++)
	{
		if(pthread_create(&thread[i], NULL, philosopher, (void *)(&id[i]) ))
		{
			fprintf(stderr, "Failed to create a new thread.\n");
			return 1;
		}
	}
	
	while(1) sleep(30);

    return 0;
}




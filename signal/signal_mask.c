/*************************************************************************
    > File Name: signal_mask.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月17日 星期日 20时38分30秒
    > Last Changed: 
    > Notes: 利用信号掩码来进行信号的阻塞和解除阻塞. 
*************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>

//进程的信号掩码给出了当前被阻塞信号的集合.


int main(int argc, char *argv[])
{
	int i;
	sigset_t intmask;		//信号掩码的数据类型为sigset_t.


	if((sigemptyset(&intmask) == -1) || sigaddset(&intmask, SIGINT) == -1)
	{
		// sigemptyset为初始化一个信号掩码，不包含任何信号
		// sigaddset为添加一个信号
		perror("Failed to initialize the signal mask");
		return -1;
	}
	
	for(;;)
	{
		// int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
		// 如果屏蔽SIGINT信号失败，则直接退出程序.
		if(sigprocmask(SIG_BLOCK, &intmask, NULL) == -1)
			break;

		fprintf(stderr, "SIGINT signal blocked...\nYou can try ^C But I think it's not useful.\n");
		sleep(5);

		fprintf(stderr, "SIGINT signal unblocked...\nYou can try ^C, I think it's useful.\n");
		fprintf(stderr, "If you blocked SIGINT before, Now it's really SIGINT.\n");
		if(sigprocmask(SIG_UNBLOCK, &intmask, NULL) == -1)
			break;
		sleep(5);
	}

	perror("Failded to change signal mask");
	return -1;
}


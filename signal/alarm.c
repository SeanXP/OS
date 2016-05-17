/****************************************************************
    Copyright (C) 2014 Sean Guo. All rights reserved.
					      									  
    > File Name:         < alarm.c >
    > Author:            < Sean Guo >
    > Mail:              < iseanxp+code@gmail.com >
    > Created Time:      < 2014/06/26 >
    > Last Changed: 
    > Description:
	SIGALRM信号处理;
	设置信号处理函数, 设置alarm时间, 用过pause()挂起进程, 等待alarm唤醒进程.
****************************************************************/

#include <unistd.h>  
#include <sys/types.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <signal.h>  

static int alarm_fired = 0;  

void ouch(int sig)  
{  
	alarm_fired = 1; //SIGALRM信号处理函数中, 仅更新状态标志alarm_fired 
}  

int main()  
{  
	//关联信号处理函数  
	signal(SIGALRM, ouch);  
	//调用alarm函数，5秒后发送信号SIGALRM  
	alarm(5);  
	//挂起进程  
	pause();  
	//接收到信号后，恢复正常执行  
	if(alarm_fired == 1) 	//收到信号则唤醒进程, 继续跑程序. 
		printf("Receive a signal %d\n", SIGALRM);  
	exit(0);  
}

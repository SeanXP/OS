/****************************************************************
  Copyright (C) 2014 Sean Guo. All rights reserved.

  > File Name:         < signal.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2014/06/26 >
  > Description:   	Unix/Linux 信号

  设置SIGINT(2)的信号处理处理函数.
 ****************************************************************/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//信号处理函数  void (*func)(int);
//唯一的参数sig表示信号, func函数根据sig的值, 决定如何处理此信号; 因此func可以处理多个信号.
void ouch(int sig)
{
    printf("\nOUCH! - I got signal %d\n", sig);
    //恢复终端中断信号SIGINT的默认行为 , 重新设置SIGINT的处理函数.
    (void) signal(SIGINT, SIG_DFL);
}

int main()
{
    //改变终端中断信号SIGINT的默认行为，使之执行ouch函数
    //而不是终止程序的执行
    (void) signal(SIGINT, ouch);
    while(1)
    {
        printf("Hello World!\n");
        sleep(1);
    }
    return 0;
}

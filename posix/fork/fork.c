/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < fork.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/03 >
  > Description:
     fork(): 创建一个新进程。与原进程几乎一模一样，同时从fork()语句的下一句开始执行。可以根据返回值的不同判断各种情况。
         父进程: 成功返回子进程的pid，失败返回负数
         子进程: 成功返回0，失败则没有创建子进程
 ****************************************************************/
#include<stdio.h>
#include<stdlib.h>  // wait()
#include<unistd.h>  // unistd.h 是C / C++提供对POSIX操作系统API的访问功能到头文件。

int main(int argc, char* argv[])
{
    pid_t pid = 0; // 记录fork()返回的pid值，用于判断父/子进程。

    printf("main process [PID:%d]\n", getpid());

    pid = fork();

    if(pid < 0)         // failed to fork
    {
        perror("fork() error");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)   // child
    {
        printf("child process [PID:%d]\n", getpid());
    }
    else                // parent
    {
        printf("parent process [PID:%d]\n", getpid());
        // wait chlid precess end
        pid = wait(0);
        printf("child process [PID:%d] end.\n", pid);
    }

    return 0;
}


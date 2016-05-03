/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < kill.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/03 >
  > Description:        fork 子进程，子进程Kill掉父进程，然后自杀的故事.

int kill(pid_t pid, int sig);
向对应PID进程发送信号sig.
pid > 0, 则发送信号;
pid == 0, 则向调用程序的进程组发送信号
若pid == -1, 则向所有kill有权发送信息的进程发送信号.
若pid为其他负数,则将信号发送到|pid|对应的进程组中去.

成功返回0，失败返回-1并设置errno.
失败原因:
1. 给定的信号无效   (errno = EINVAL)
2. 发送权限不够     (errno = EPERM)
3. 目标进程不存在   (errno = ESRCH)

----

进程可以调用alarm函数在经过预定时间后向发送一个SIGALRM信号, 实现定时效果.
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
如果seconds为0，将取消所有已设置的闹钟请求。
alarm函数的返回值是以前设置的闹钟时间的余留秒数，如果返回失败返回-1。

int raise(int sig);
raise函数向自己发送一个sig信号
成功返回0，失败返回非零的错误值并设置errno.
其中sig是无效的则将errno设置为EINVAL.

 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>         // kill()
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t child = 0;    // 记录fork()返回的pid值，用于判断父/子进程。

    printf("main [PID:%d]\n", getpid());

    child = fork();

    if(child < 0)           // failed to fork
    {
        perror("fork() error");
        exit(EXIT_FAILURE);
    }
    else if(child == 0)     // child
    {
        printf("child [PID:%d], parent [PID:%d]\n", getpid(), getppid());

        //5秒后向父进程SIGTERM信号, 结束父进程.
        fprintf(stderr, "Ok, child [PID:%ld] will kill parent [PPID:%ld] in 5 seconds.\n",
                (long)getpid(), (long)getppid());
        sleep(5);
        fprintf(stderr, "!!! kill !!!\n");
        if(kill(getppid(), SIGTERM) == -1)
        {
            perror("failed to kill parent process");
            exit(EXIT_FAILURE);
        }

        sleep(1);
        //查看现在子进程的PPID, 理论上孤儿进程将被init(PID:1)收养.
        fprintf(stderr, "Now, I think I am a orphan... [PPID:%ld]\n", (long)getppid());
        fprintf(stderr, "Ok, now I will kill myself.\n");

        //用过raise向自身进程发送信号;
        if(raise(SIGTERM) == -1)
        {
            perror("failed to kill myself");
            exit(EXIT_FAILURE);
        }

        // never run this code.
        fprintf(stderr, "Why I still alive?\n");
    }
    else                    // parent
    {
        printf("parent [PID:%d], child [PID:%d]\n", getpid(), child);
        //不断打印自己的存活信息;
        //等待子进程的kill.
        int i;
        for(i = 1; i < 100; i++)
        {
            sleep(1);
            fprintf(stderr, "Parent [PID:%ld] is alive %d seconds...\n",
                    (long)getpid(), i);
        }
    }

    return 0;
}

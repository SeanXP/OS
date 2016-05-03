/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < waitpid.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/03 >
  > Description:

#include <sys/types.h>
#include <sys/wait.h>


int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
----
    pid_t wait(int *status);

    进程一旦调用了 wait，就立即阻塞自己，由wait自动分析是否当前进程的某个子进程已经退出.
    如果找到一个已经变成僵尸的子进程，wait就会收集这个子进程的信息，并把它彻底销毁后返回；
    如果没有找到这样一个子进程，wait就会一直阻塞，直到有一个出现为止。
    参数status用来保存被收集进程退出时的一些状态，它是一个指向int类型的指针。
    pid = wait(NULL); // 不关心子进程的状态;

    返回:   如果成功，wait会返回被收集的子进程的进程ID;
            如果调用进程没有子进程，调用就会失败，wait返回-1，同时errno被置为ECHILD。
----
    pid_t waitpid(pid_t pid, int *status, int options);

    pid :
        pid > 0,    只等待进程ID等于pid的子进程;
        pid = -1,   等待任何一个子进程退出，没有任何限制，等价wait();
        pid = 0,    等待同一个进程组中的任何子进程，如果子进程已经加入了别的进程组，waitpid不会对它做任何理睬。
        pid < -1,   等待一个指定进程组中的任何子进程，这个进程组的ID等于pid的绝对值。
    options:
        WNOHANG,    不阻塞, 没有任何已终止的进程则立即返回;
        WUNTRACED,  如果子进程进入暂停执行则马上返回，但终止状态不予理睬。

    wait()就是包装过的waitpid();
    static inline pid_t wait(int * wait_stat) {return waitpid(-1,wait_stat,0);}

    返回值:
        ret > 0, 当正常返回的时候，waitpid返回收集到的子进程的进程ID;
        ret = 0, 如果设置了选项WNOHANG，而调用中waitpid发现没有已退出的子进程可收集，则返回0;
        ret = -1, 如果调用中出错，则返回-1, 并设置errno;
        ret = -1, erron = ECHILD: 当pid所指示的子进程不存在，或此进程存在，但不是调用进程的子进程，waitpid就会出错返回，errno被设置为ECHILD;

 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>         // exit()
#include <sys/wait.h>       // waitpid()
#include <unistd.h>         // sleep()

int main(int argc, char* argv[])
{
    pid_t pid = 0; // 记录fork()返回的pid值，用于判断父/子进程。

    printf("main [PID:%d]\n", getpid());

    pid = fork();

    if(pid < 0)         // failed to fork
    {
        perror("fork() error");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)   // child
    {
        printf("child [PID:%d], parent [PID:%d]\n", getpid(), getppid());
        sleep(2);
    }
    else                // parent
    {
        printf("parent [PID:%d], child [PID:%d]\n", getpid(), pid);
        // wait chlid precess end

        /*pid = wait(NULL);*/
        pid = waitpid(pid,NULL,0);
        printf("child process [PID:%d] end.\n", pid);
    }

    return 0;
}

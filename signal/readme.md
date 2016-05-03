kill()
====

向对应PID进程发送信号sig.

    int kill(pid_t pid, int sig);

参数pid:

* pid > 0, 则发送信号;
* pid == 0, 则向调用程序的进程组发送信号;
* pid == -1, 则向所有kill有权发送信息的进程发送信号;
* pid为其他负数,则将信号发送到|pid|对应的进程组中去.

成功返回0，失败返回-1并设置errno.

失败原因:

1. 给定的信号无效   (errno = EINVAL)
2. 发送权限不够     (errno = EPERM)
3. 目标进程不存在   (errno = ESRCH)

###alarm()

进程可以调用alarm函数在经过预定时间后向发送一个SIGALRM信号, 实现定时效果.

    #include <unistd.h>
    unsigned int alarm(unsigned int seconds);

如果seconds为0，将取消所有已设置的闹钟请求。
alarm函数的返回值是以前设置的闹钟时间的余留秒数，如果返回失败返回-1。

###raise()

    int raise(int sig);

raise函数向自己发送一个sig信号;
成功返回0，失败返回非零的错误值并设置errno;
其中sig是无效的则将errno设置为EINVAL.

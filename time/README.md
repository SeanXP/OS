time
====

## 时间类型

* 真实时间
    * 从某一标准点开始度量真实时间，为日历时间（calendar time），适用于需要打上时间戳的程序；
    * 从进程生命周期内的某一固定时点（通常为程序起点）开始度量真实时间，为流逝时间（elapsed clock）或挂钟时间（wall clock），主要针对需要周期性操作的程序等；
* 进程时间，一个进程所使用的CPU时间总量，适用于对程序、算法性能的检查和优化；

## 日历时间（calendar time）

UNIX系统内部对时间的表示方法均是自 Epoch 以来的秒数来度量的。Epoch，即通用协调时间（UTC）的1970年1月1日早晨零点。这也是UNIX大致问世的时间。
日历时间存储于`time_t`的变量中。

### 2038年困扰
在32位Linux系统中，`time_t`是一个有符号整数，可表示的日期从1901年12月13日20时45分52秒至`2038年1月19日03:14:07`，因此，当前许多32位UNIX系统都面临一个2038年的理论问题。
只有到2038年时，所以的UNIX系统都早已升级为64位系统，才会能解决这一问题。然而32位嵌入式系统，由于其寿命较之台式机硬件更长，故而仍然会受此问题的困扰。

### gettimeofday — get the date and time

    #include <sys/time.h>

    int gettimeofday(struct timeval *restrict tp, void *restrict tzp);

    return 0 and no value shall be reserved to indicate an error.

struct timeval结构体：

    The structures pointed to by tp and tzp are defined in <sys/time.h> as:

    struct timeval {
        time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
        suseconds_t  tv_usec;  /* and microseconds */
    };

* `tv_sec`提供秒级精度，`time_t`为`long int`；
* `tv_usec`提供微妙级精度（要与`tv_sec`相加，才能表示时间），`suseconds_t`为`int`，其返回值的准确性则依赖于构架的具体实现。
* 参数`tzp`为历史产物，如今已废弃不用，应始终置为NULL；

### time - get time in seconds

    #include <time.h>

    time_t time(time_t *tloc);

    Returns number of seconds since the Epoch, or (time_t)(-1) on error;

`time()`有两种返回方式，可以从参数`tloc`存放返回值，也会直接返回time_t结构体。

### ctime()

    #include <time.h>

    char *ctime(const time_t *timep);

    Returns pointer to statically allocated string terminated by newline and '\0' on success,
    or NULL on error;

**调用ctime()、gmtime()、localtime()、asctime()任一函数，都可能覆盖由其他函数返回，且静态分配的数据结构。如果需要维护返回的信息，则必须将其返回保存到本地副本。**

### gmtime(), localtime() 分解时间

    #include <time.h>

    char *asctime(const struct tm *tm);
    char *asctime_r(const struct tm *tm, char *buf);

    char *ctime(const time_t *timep);
    char *ctime_r(const time_t *timep, char *buf);

    struct tm *gmtime(const time_t *timep);
    struct tm *gmtime_r(const time_t *timep, struct tm *result);

    struct tm *localtime(const time_t *timep);
    struct tm *localtime_r(const time_t *timep, struct tm *result);

函数`gmtime()`和`localtime()`可将`time_t`值转换为分解时间（broken-down time），置于一个静态分配的结构中，返回其地址；

* gmtime()将日历时间转换为对应于UTC的分解时间；
* localtime()将日历时间转换为对应于系统本地时间的分解时间；

broken-down time：

    Broken-down time is stored in the structure tm, which is defined in <time.h> as follows:

    struct tm {
        int tm_sec;    /* Seconds (0-60) */
        int tm_min;    /* Minutes (0-59) */
        int tm_hour;   /* Hours (0-23) */
        int tm_mday;   /* Day of the month (1-31) */
        int tm_mon;    /* Month (0-11) */
        int tm_year;   /* Year - 1900 */
        int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
        int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
        int tm_isdst;  /* Daylight saving time */
    };

### timezone

不同国家使用不同的时区和夏时制。时区信息往往繁琐多变，因此系统没有将其直接编码于程序或函数，而是以标准形式保存于文件中，并加以维护。

时区目录`/usr/share/zoneinfo`，该目录下的每个文件都包含了一个特定国家或地区内时区制度的相关信息。

    $ cd /usr/share/zoneinfo
    $ file UTC
    UTC: timezone data, version 2, 1 gmt time flag, 1 std time flag, no leap seconds, no transition times, 1 abbreviation char
    $ file Asia/Shanghai
    Asia/Shanghai: timezone data, version 2, 3 gmt time flags, 3 std time flags, no leap seconds, 17 transition times, 3 abbreviation chars
系统的本地时间由时区文件`/etc/localtime`定义，通常链接到`/usr/share/zoneinfo`的某一个时区文件。

    $ ll /etc/localtime
    lrwxrwxrwx 1 root root 33 Mar  1 09:09 /etc/localtime -> /usr/share/zoneinfo/Asia/Shanghai

## 进程时间
进程时间，一个进程所使用的CPU时间总量，出于记录的目的，内核将其分为两部分：

* 用户 CPU 时间，在用户模式下所执行指令所花费的时间数量。也称为虚拟时间（virtual time），对于程序来说是其得到CPU的时间。
* 系统 CPU 时间，在内核模式下所执行指令所花费的时间数量。为内核执行系统调用或代表该程序执行其他任务（例如，服务页错误）的时间。

可以使用`time`命令，获得运行程序的时间：

    $ time du /home/xxx
    du /home/xxx  0.01s user 0.03s system 95% cpu 0.045 total

### times - get process times

    #include <sys/times.h>
    clock_t times(struct tms *buf);

    Returns number of clock ticks (sysconf(_SC_CLK_TCK)) since "arbitrary" time in past on success, or (clock_t)(-1) on error;
`times()`检索进程时间信息，并把结果通过buf指向的结构体返回。

    times() stores the current process times in the struct tms that buf points to.  The struct tms is as defined in <sys/times.h>:

    struct tms {
        clock_t tms_utime;  /* user time */
        clock_t tms_stime;  /* system time */
        clock_t tms_cutime; /* user time of children */
        clock_t tms_cstime; /* system time of children */
    };

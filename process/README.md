process
====

**进程（process）是一个可执行程序（program）的示例。**

一个程序可以创建多个进程。进程是由内核定义的抽象的实体，并为该实体分配用以执行程序的各项系统资源。

从内核的角度，进程有用户内存空间（user-space memory）和一系列内核数据结构组成。

* 用户内存空间，包含程序代码以及代码变量。
* 内核数据结构，用于维护进程状态信息。例如标识号（PID）、虚拟内存表、打开文件的描述符表、信号传递、当前工作目录等。

## 程序 program

程序是包含一系列信息的文件，这些信息描述了如何在运行是创建一个进程（或多个进程），包括以下内容：

* 二进制格式标识，内核用此信息来解释文件的其他信息。UNIX/Linux使用可执行连接格式（ELF）。
* 机器语言指令，对程序算法进行编码。
* 程序入口地址，标识程序开始时的起始指令位置；
* 数据：变量初始值，字面常量值；
* 符号表及重定位表：描述程序中函数和变量的位置及名称，用于运行时的符号解析（动态链接）和调试信息等。
* 共享库和动态链接信息：指明运行所需的共享库、动态链接器路径等。
* 其他信息

## getpid

    #include <unistd.h>

    pid_t getpid(void);
    pid_t getppid(void);

    The getpid() and getppid() functions are always successful, and no return value is reserved to indicate an error.

* Linux内核限制的进程号需小于等于32767，新进程创建时内核按顺序将下一个可用的进程号分配给其使用，当达到32767限制，内核将重置进程计数器（重置为300，而非1，因此低数值的PID为系统进程与守护进程所长期占用）。
* Mac OS X对PID的限制不是32767；

Linux的PID限制（Linux ArchLinux 4.5.4-1-ARCH Linux ArchLinux 4.5.4-1-ARCH）：

    $ cat /proc/sys/kernel/pid_max
    32768
一般在32位平台，pid_max为32768，在64位平台可以更大（不过目前很多64位Linux仍是32768，如上例）。

除了`getppid()`，也可以通过`/proc/PID/status`的PPID字段查看ppid；

## 进程内存布局 segment

每个进程所分配的内存有很多部分组成，称为“段”（segment），表示对UNIX系统中进程虚拟内存的逻辑划分。

* 文本段（只读属性）。包含进程运行的程序机器语言指令。文本段只读属性，防止进程通过错误指针意味修改自身指令，又可以共享给同一程序的其他进程（映射到其他进程的虚拟地址空间）。
* 初始化数据段（用户初始化数据段， user-initialized data segment）。包含显示初始化的全局变量和静态变量（占用可执行文件的磁盘空间）。当程序加载到内存时，从可执行文件中读取这些变量的值。
* 未初始化数据段（零初始化数据段， zero-initialized data segment）。包含未初始化的全局变量和静态变量（不占用磁盘空间）。当加载程序时，分配这段内存，并初始化为0。
* 栈，动态增长和收缩的段，由栈帧（stack frames）组成。系统为每个当前调用的函数分配一个栈帧，存储函数的局部变量、实参、返回值。
* 堆，动态进行分配内存的段。

由于历史原因，未初始化数据段常被称之为BSS段，源于老版本的汇编语言助记符"block started by symbol"；将初始化的全局变量和静态变量与未初始化的全局变量和静态变量分开存放，注意原因是程序在磁盘上存储时，没有必要为未初始化的全局变量和静态变量分配存储空间。
相反，可执行文件只需要记录未初始化数据段的位置及所需大小，直到程序运行时再由程序加载器来分配此段内存。

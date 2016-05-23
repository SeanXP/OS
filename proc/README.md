/proc 虚拟文件系统
====

为了提供简单的方法来访问内核信息，UNIX实现提供了一个/proc虚拟文件系统。

* 驻留在`/proc`目录，包含各种展示内核信息的文件；
* 允许进程通过常规I/O系统调用来读取，甚至修改；
* 不占用磁盘空间，由内核在进程访问文件时动态创建；

### PID

对于系统中的每个进程，内核都提供相应的目录，命名为`/proc/PID`，其中PID为进程的特定PID数字；目录中包含进程的相关信息。

查看进程`init`（PID：1）的状态信息：

    $ cat /proc/1/status | head                                                                                                                                          !1081
    Name:   systemd
    State:  S (sleeping)
    Tgid:   1
    Ngid:   0
    Pid:    1
    PPid:   0
    TracerPid:      0
    Uid:    0       0       0       0
    Gid:    0       0       0       0
    FDSize: 64

PID目录下的文件：

* `cmdline`，命令行参数
* `cwd`，指向当前工作目录的符号连接
* `environ`，环境列表
* `exe`，指向对应可执行文件的符号连接
* `fd`，文件目录，包含进程打开文件的符号连接
* `maps`，内存映射
* `mem`，进程虚拟内存
* `mounts`，进程的安装点
* `root`，指向根目录的符号连接
* `status`，进程状态信息
* `task`，每个线程对应对应一个子目录

### /proc 子目录

* `/proc/net`，有关网络和套接字的状态信息
* `/proc/sys/fs`，文件系统相关设置
* `/proc/sys/kernel`，各种常规的内核设置
* `/proc/sys/net`，网络和套接字设置
* `/proc/sys/vm`，内存管理设置
* `/proc/sysvipc`，有关System V IPC的信息


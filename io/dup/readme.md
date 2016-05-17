dup
====

## dup, 复制文件描述符

    #include <unistd.h>
    int dup(int oldfd);
    Return (new) file descriptor on success, or -1 on error;

dup()复制一个打开的文件描述符oldfd, 并返回一个新描述符，两者都指向同一个打开的文件句柄。系统保证新描述符一定是编号值最低的未用文件描述符。

如要实现`$ ls 2>&1`的功能，即将文件描述符1复制给文件描述符2，让两者指向相同的文件句柄(stdin)：

    close(2);
    newfd = dup(1);

上面的代码只有当文件描述符0已打开，newfd 才为2；为了明确指定新描述符的编号，建议使用`dup2(1,2);`;

dup2()会为oldfd所指定的文件描述符创建副本，编号由newfd指定。如果newfd之前已打开，则dup2()会先将其关闭，然后再复制。

    #include <unistd.h>
    int dup2(int oldfd, int newfd);
    Return (new) file descriptor on success, or -1 on error;

如果oldfd为无效的文件描述符，则error置EBADF，且不关闭newfd;

    newfd = fcntl(oldfd, F_DUPFD, startfd);

为oldfd创建一个副本，且将使用大于等于startfd的最小未用值作为新描述符；

**文件描述符的正、副本之间共享同一打开的文件句柄所含的文件偏移量和状态标志，但是新文件描述符也有一套自己的文件描述符标志，且其close-on-exec标志（FD_CLOEXEC）总是处于关闭状态。**

    #define _GUN_SOURCE
    #include <unistd.h>

    int dup3(int oldfd, int newfd, int flags);
    Return (new) file descriptor on success, or -1 on error;

## 源码分析

dup系统调用的服务例程为`sys_dup()`，定义在`kernel/fs/fcntl.c`中。`sys_dup()`的代码也许称得上是最简单的代码之一，但是就是这么一个简单的系统调用，却成就了linux系统最著名的一个特性：**输入/输出重定向**。

### sys_dup()
`sys_dup()`的主要工作就是用来“复制”一个打开的文件号，并使两个文件号都指向同一个文件：

    asmlinkage long sys_dup(unsigned int fildes) //sys_dup函数的参数，即fildes，是文件描述符fd
    {
        int ret = -EBADF;
        struct file * file = fget(fildes); //通过文件描述符找到对应的文件


        if (file)
            ret = dupfd(file, 0); //分配一个新的文件描述符fd，并将fd和file联系起来
        return ret;
    }
### fget()

fget(int fd), 通过文件描述符fd，返回对应的文件指针;
kernel代码中有一个current变量，它是一个指针(`struct task_struct *`)，用来指向执行当前这段kernel代码的进程。

    struct file fastcall *fget(unsigned int fd)
    {
        struct file *file;
        struct files_struct *files = current->files;    //获得当前进程的打开文件表


        rcu_read_lock();                                // RCU(Read-Copy Update)，顾名思义就是读-拷贝修改，它是基于其原理命名的。
        file = fcheck_files(files, fd);                 //根据fd从打开文件表files里取出相应的file结构变量
        if (file) {
            if (!rcuref_inc_lf(&file->f_count)) {       //增加引用
                /* File object ref couldn't be taken */
                rcu_read_unlock();
                return NULL;
            }
        }
        rcu_read_unlock();
        return file;
    }

    static inline struct file * fcheck_files(struct files_struct *files, unsigned int fd)
    {
        struct file * file = NULL;
        struct fdtable *fdt = files_fdtable(files);


        if (fd < fdt->max_fds)
            file = rcu_dereference(fdt->fd[fd]);
        return file;
    }

### dupfd(file, 0)

`dupfd(file, 0)`，分配一个新的文件描述符fd，并将fd和file联系起来；

    static int dupfd(struct file *file, unsigned int start)
    {
        struct files_struct * files = current->files;
        struct fdtable *fdt;
        int fd;

        spin_lock(&files->file_lock);
        fd = locate_fd(files, file, start);         //分配文件描述符
        if (fd >= 0) {
            /* locate_fd() may have expanded fdtable, load the ptr */
            fdt = files_fdtable(files);             //获得文件描述符表
            FD_SET(fd, fdt->open_fds);              //设置打开文件标记
            FD_CLR(fd, fdt->close_on_exec);
            spin_unlock(&files->file_lock);
            fd_install(fd, file);                   //建立fd和file的联系，之后通过fd就可以找到file
        } else {
            spin_unlock(&files->file_lock);
            fput(file);
        }

        return fd;
    }

### init

内核初始化中的相关源码分析:

    static int init(void * unused)
    {
        ...
        if (sys_open((const char __user *) "/dev/console", O_RDWR, 0) < 0)
            printk(KERN_WARNING "Warning: unable to open an initial console.\n");
        //打开控制台/dev/console，这样init进程就拥有一个控制台，并通过文件描述符0从中读取输入信息，也可以向其中写入信息；

        //调用dup打开/dev/console文件描述符两次，这样控制设备也可以供标准输出和标准错误使用(文件描述符为1和2)
        (void) sys_dup(0);
        (void) sys_dup(0);

        //如果sys_open((const char __user *) "/dev/console", O_RDWR, 0) 成功执行，init进程到这里就拥有3个文件描述符(标准输入、标准输出和标准错误);
        ...
    }
## 系统重定向

    $ echo hello

在shell下输入如下命令：`echo hello`，这条命令要求shell进程执行一个可执行文件echo，参数为"hello"。
当shell接收到命令之后，先找到`/bin/echo`可执行命令，然后fork()出一个子进程执行`/bin/echo`，并将参数传递给它，而这个进程从shell继承了三个标准文件，即标准输入（stdin），标准输出（stdout）和标准出错信息（stderr），它们三个的文件号分别为0、1、2。

echo进程的工作很简单，就是将参数"hello"写到标准输出文件(fd == 1)中去，通常都是我们的显示器上。

如果我们将命令改成`echo hello > hello.txt`，则在执行时输出(fd == 1)将会被重定向到磁盘文件hello.txt中。
我们假定在此之前该shell进程只有三个标准文件打开，文件号分别为0、1、2，以上命令行将按如下序列执行：

1. 打开或创建磁盘文件hello.txt，如果hello.txt中原来有内容，则清除原来内容（因为命令中为`> hello.txt`，表示覆盖目标文件），其文件描述符为3；
2. 通过dup()复制标志输出stdout，即把文件描述符1(stdout)对应的file结构指针复制到文件描述符4处，目的是将stdout的file指针暂时保存一下;
3. 关闭文件描述符1(stdout)，但是由于4号文件对stdout原有的file结构指针也有个引用，所以stdout文件并未真正关闭，只是腾出1号文件文件描述符的位置而已；
4. 通过dup()，复制文件描述符3（即磁盘文件hello.txt），由于文件描述符1已关闭，其位置空缺，dup分配的新文件描述符为最小未用的1号，即进程中原来指向stdout的指针指向了hello.txt文件；
5. 通过系统调用fork()和exec()创建子进程并执行echo，子进程在执行echo前关闭文件描述符3和4，只留下0、1、2三个文件，请注意，这时的1号文件已经不是stdout而是磁盘文件hello.txt。当echo想向stdout文件写入"hello"时自然就写入到了磁盘文件hello.txt中。
6. 回到shell后，关闭指向foo的1号与3号文件，再用dup()和close()将2号恢复至stdout，这样shell就恢复了0、1、2三个标准输入/输出文件。

由此可见，当echo程序（或其他）在运行的时候并不知道stdout（对于stdin和stderr同样）指向什么，进程与实际输出文件或设备的结合是在运行时由其父进程“包办”的。
这样就简化了子进程的程序设计，因为在设计时只要跟三个逻辑上存在的文件打交道就可以了，类似于面向对象中的多态和重载。

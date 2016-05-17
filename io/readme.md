通用IO
====

## standard file descriptor

| file descriptor | POSIX name | stdio stream |
| :---: | :---: | :---: |
| 0 | STDIN_FILENO | stdin |
| 1 | STDOUT_FILENO | stdout |
| 2 | STDERR_FILENO | stderr |

* 标准输出是行缓冲的，在缓冲区被填满或遇到换行符号前不会输出。 对于stdout，`\n`意味着换行与清空缓冲区；
* 标准错误是不缓冲的，所以语句执行完后立刻显示出来。 对于stderr，`\n`只意味换行；

## open

    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *path, int flags, ...);
    int open(const char *path, int flags, mode_t perms);

    int openat(int fd, const char *path, int oflag, ...);

The open() function shall establish the connection between a file and a file descriptor.

* path: 文件路径名
* flags:
    * 文件访问模式：O_RDONLY 只读, O_WRONLY 只写, O_RDWR 读写访问
    * 文件创建模式：O_TRUNC 写前清空原文件，O_CREAT 创建文件必须指定权限，O_CREAT | O_EXCL（文件不存在则创建文件， 已存在则返回错误），
      O_NOCTTY 防止打开的设备变成控制终端，O_APPEND 添加至文件末尾，0_ASYNC（当I/O操作可行则产生信号通知进程），O_DSYNC（提供同步I/O数据完整性），
      O_SYNC（以同步方式写入文件），O_NONBLOCK 不等待命名管道或特殊文件
    * 已打开文件的状态标志：
* perms: permissions (when creating), looks like 'S_I1222' ( 1: R/W/X, 222: USR/GRP/OTH)
    * S_IRUSR | S_IWUSR | S_IXUSR
    * S_IRGRP | S_IWGRP | S_IXGRP
    * S_IROTH | S_IWOTH | S_IXOTH

Upon successful completion, these functions shall open the file and return a non-negative integer representing the lowest numbered unused file descriptor.
Otherwise, these functions shall return −1 and set errno to indicate the error. If −1 is returned, no files shall be created or modified.

## read

    #include <unistd.h>

    ssize_t read(int fd, void *buffer, size_t count);
    // returns number of bytes read, 0 on EOF, or -1 on error

系统调用不会分配内存缓存区，因此需要预先分配足够大小的缓冲区并传递指针给系统调用read()；

* 如果read()从stdin读取，则遇到换行符`\n`，read()调用就结束。
* 如果read()从文件读取，则遇到换行符`\n`不会结束。

read()不会自动在接受到的字符串后加`\0`，因为read()用于读取多类设备，多类格式（二进制、文本），所以无法遵从C语言对字符串处理的约定。

**因此在C语言中调用read()需要显式追加`\0`，同时要保证缓冲区大小**：

    char buffer[MAX + 1];
    if((ret = read(STDIN_FILENO, buffer, MAX)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';

## write

    #include <unistd.h>

    ssize_t write(int fd, void *buffer, size_t count);
    // returns number of bytes written, or -1 on error

返回实际写入文件的字节数，返回值可能小于`count`，这种情况称为`部分写`，对于磁盘文件，造成“部分写”的原因：

* 磁盘已满，无法写完`count`个字节；
* 进程资源对文件大小的限制，`RLIMIT_FSIZE`；

## close

    #include <unistd.h>
    int close(int fd);

显式关闭不再需要的文件描述符是良好的编程习惯。

企图关闭一个未打开的文件描述符，或两次关闭同一个描述符，返回-1并设置error；

## lseek

对于每个打开的文件，系统都会记录其文件偏移量。

    #include <unistd.h>

    off_t lseek(int fd, off_t offset, int whence);
    // Returns new file offset if successful, or -1 on error

* offset，偏移值，单位：字节；
* whence，偏移参考基点：
    * SEEK_SET，从文件头部起始点开始偏移offset字节。
    * SEEK_CUR，从文件当前偏移量开始偏移offset字节。
    * SEEK_END，从文件结尾开始偏移offset字节。

示例：

    lseek(fd, 0, SEEK_SET);         // start of file
    lseek(fd, 0, SEEK_END);         // next by after the end of the file
    lseek(fd, -1, SEEK_END);        // Last byte of file
    lseek(fd, -10, SEEK_CUR);       // Ten bytes prior to current location
    lseek(fd, 10000, SEEK_END);     // 10001 bytes past last byte of file

**lseek()只是调整内核中与文件描述符相关的文件偏移量记录（一个变量），并没有引起对任何物理设备的访问。**

**lseek()并不适用于所有类型的文件，不允许将lseek()用于pipe/FIFO/socket/tty，否则会调用失败并置errno为ESPIPE。**

### 文件空洞
文件偏移量跨越EOF，然后使用write()系统调用写入数据，则中间这段空间称为文件空洞。从编程角度看，文件空洞是存在字节的，读取空洞将返回以0（空字节'\0'）填充的缓冲区。

例如，新建文件，通过`lseek(fd, 1000, SEEK_SET)`，然后拷贝hello.txt的文件到新文件中：

    ls -l *.txt
    -rw-r--r-- 1 gxp staff   29 May 16 15:25 hello.txt
    -rw-r--r-- 1 gxp staff 1029 May 16 15:38 test.txt

    du *.txt
    4       hello.txt
    4       test.txt

虽然`ls -l`下的数据大小不同，看是`du`查看磁盘占用，两个文件都占用4k磁盘空间（最小的磁盘分配空间）。

### Mac OS X - file hole
测试环境：Mac OS X - Darwin Kernel Version 15.4.0

如果增大文件空洞，就有区别：

    create new file and lseek to 1000000 and write something.
    write to file: ./test.txt
    ls -l *.txt
    -rw-r--r-- 1 gxp staff      29 May 16 15:25 hello.txt
    -rw-r--r-- 1 gxp staff 1000029 May 16 16:17 test.txt
    du *.txt
    4       hello.txt
    980     test.txt
现在`hello.txt`占用4k磁盘空间，实际使用空间为29字节。
`test.txt`占用980k磁盘空间，实际使用空间为（1000000字节的空洞+29字节数据）。

### Linux - file hole
测试环境：Linux ArchLinux 4.5.4-1-ARCH

    create new file and lseek to 1000000 and write something.
    write to file: ./test.txt
    ls -l *.txt
    -rw-r--r-- 1 gxp users      29 May 16 16:30 hello.txt
    -rw-r--r-- 1 gxp users 1000029 May 16 16:32 test.txt
    du *.txt
    4       hello.txt
    4       test.txt

### 对比

* Mac OS X对文件空洞的处理，就是直接使用`\0`填充，所以Mac OS X系统下是不存在所谓的`稀疏文件`。
* Linux对文件空洞的处理，是不分配空洞所占用的磁盘空间，例如`test.txt`，前1000000字节为文件空洞，则不分配磁盘空间，只分配后29字节所需的磁盘空间（一个磁盘块，4K）。

这样的文件叫做`稀疏文件`，核心转储文件(core dump)就是这样的文件。

### 不同命令对文件空洞的处理

* `ls`下的数据大小是统计文件空洞的。
* `vim`下可以看到`^@^@^@^@^@^@^@`，之后才是我们写入的ASCII数据。
* `cat`自动跳过文件空洞，只显示正常的数据。
* `od`下可以看到，文件空洞部分数据都是`0x00`。
* `cp`复制文件时也会复制相同的文件空洞。
* `cat test.txt > copy.txt`，对于Mac OS X，其本来就以填充文件空洞并分配磁盘空间，所以`copy.txt`与`test.txt`都会很大；对于Linux，`test.txt`的文件空洞并不占用磁盘空间，但是`cat >`会将文件空洞填充且占用磁盘空间，`copy.txt`很占磁盘空间。

作用：空洞文件作用很大，例如迅雷下载文件，在未下载完成时就已经占据了全部文件大小的空间，这时候就是空洞文件。下载时如果没有空洞文件，多线程下载时文件就都只能从一个地方写入，这就不是多线程了。如果有了空洞文件，可以从不同的地址写入，就完成了多线程的优势任务。

### cp命令流程分析

cp命令可以识别文件中是否含有文件空洞，并在拷贝过程中生成相同的文件空洞。

1. 判断目标文件是否存在，如果存在则清空目标文件，如果不存在则创建目标文件
2. 根据目标文件的逻辑块大小，创建拷贝缓冲区
3. 判断源文件是否有空洞：文件大小／文件块大小 > 块数 ？
4. 读取源文件存放到缓冲区，每次读取一块
5. 在第3步中判断，如果存在文件空洞，则对缓冲区数据进行判断，如果缓冲区中的数据均为0，则认为该数据快为空洞，否则认为是正常文件数据
6. 如果数据块为空洞，则调用lseek，在目标文件中创建一个空洞；否则拷贝缓冲区数据到目标文件
7. 判断本次读取是否读到源文件的文件尾，如果是，则判断本次读取的是否是空洞，如果是空洞则在文件的最后写入""
8. 重复1 ~ 7
9. 关闭目标文件、源文件

## 系统调用的原子性

所有系统调用都是以原子操作方式执行的，这样内核保证了某系统调用中的所有步骤会作为独立操作而一次性加以执行，期间不会为其他进程或线程所中断。

open()调用时，`O_CREAT | O_EXCL`保证当打开的文件已存在时返回一个错误，这样可以保证进程是打开文件的创建者。对文件检查是否存在和创建文件属于同一原子操作，如果先调用open()检查是否存在，再调用open()创建新文件，这样的非原子操作可能会导致多个相同进程都以为自己是文件的创建者。

## fcntl - file control

    #include <fcntl.h>
    int fcntl(int fd, int cmd, ...);
    Return on success depends on cmd, or -1 on error;

fcntl()执行描述符控制操作;

cmd:

* `F_DUPFD`, 复制现有的描述符;
* `F_GETFD` / `F_SETFD`, 获得/设置描述符标记;
* `F_GETFL` / `F_SETFL`, 获得/设置描述符状态;
* `F_GETOWN` / `F_SETOW`,获得/设置异步I/O所有权;
* `F_GETLK` / `F_SETLN`, 获得/设置记录锁.

常用用法:

* 非阻塞式I/O:  	`fcntl(fd, F_SETFL, O_NONBLOCK);`
* 信号驱动I/O:	`fcntl(fd, F_SETFL, O_ASYNC);`
* 设置套接字属主: `fcntl(fd, F_SETOWN, pid);`, 指定用于接收SIGIN & SIGURG信号的套接字属主,
进程组id通过提供负值的arg来说明(arg绝对值的一个进程组ID)，否则arg将被认为是进程id;
* 获取套接字属主: `fcntl(fd, F_GETOWN);`, 获取套接字的当前属主, 返回值为PID;

通用IO
====

## standard file descriptor

| file descriptor | POSIX name | stdio stream |
| :---: | :---: | :---: |
| 0 | STDIN_FILENO | stdin |
| 1 | STDOUT_FILENO | stdout |
| 2 | STDERR_FILENO | stderr |

## open()

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

## read()

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

## write()

    #include <unistd.h>

    ssize_t write(int fd, void *buffer, size_t count);
    // returns number of bytes written, or -1 on error

返回实际写入文件的字节数，返回值可能小于`count`，这种情况称为`部分写`，对于磁盘文件，造成“部分写”的原因：

* 磁盘已满，无法写完`count`个字节；
* 进程资源对文件大小的限制，`RLIMIT_FSIZE`；

## close()

    #include <unistd.h>
    int close(int fd);

显式关闭不再需要的文件描述符是良好的编程习惯。

企图关闭一个未打开的文件描述符，或两次关闭同一个描述符，返回-1并设置error；


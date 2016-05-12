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
## write()
## close()

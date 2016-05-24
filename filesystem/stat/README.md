stat - get file status
====

    #include <sys/stat.h>

    int stat(   const char *restrict pathname,   struct stat *restrict buf);
    int lstat(  const char *restrict pathname,   struct stat *restrict buf);
    int fstat(  int fd,                          struct stat *buf);

* stat()返回命名文件的信息；
* lstat()类似stat()，不过如果为符号链接，则返回符号链接自身，而非指向的文件；
* fstat()利用打开的文件描述符来访问文件；

成功返回0，失败返回-1并设置errno.

restrict修饰符号说明不允许path和buf产生重叠。 reserved为C语言中的一种类型限定符，用于告诉编译器，对象已经被指针所引用，不能通过除该指针外所有其他直接或间接的方式修改该对象的内容。

结构体 struct stat

    All of these system calls return a stat structure, which contains the following fields:

    struct stat {
        dev_t     st_dev;         // ID of device containing file
        ino_t     st_ino;         // inode number
        mode_t    st_mode;        // file type and mode
        nlink_t   st_nlink;       // number of hard links
        uid_t     st_uid;         // user ID of owner
        gid_t     st_gid;         // group ID of owner
        dev_t     st_rdev;        // device ID (if special file)
        off_t     st_size;        // total size, in bytes
        blksize_t st_blksize;     // blocksize for filesystem I/O
        blkcnt_t  st_blocks;      // number of 512B blocks allocated

        // Since Linux 2.6, the kernel supports nanosecond precision for the following timestamp fields.
        // For the details before Linux 2.6, see NOTES.

        struct timespec st_atim;  // time of last access
        struct timespec st_mtim;  // time of last modification
        struct timespec st_ctim;  // time of last status change

    #define st_atime st_atim.tv_sec      // Backward compatibility
    #define st_mtime st_mtim.tv_sec
    #define st_ctime st_ctim.tv_sec
    };

### output

    $ gcc stat.c  -o stat

    $ ./stat Makefile
    device inode:       16777220
    inode number:       105054180
    permissions:        33188
    hard link number:   1
    UID:                501
    GID:                20
    device type:        0
    last access time:   Tue May 24 21:15:32 2016
    last modify time:   Tue May 24 21:15:31 2016
    last status time:   Tue May 24 21:15:31 2016
    file size:          302
    block number:       8
    block size:         4096

* `st_dev`，表示文件所在的设备。
* `st_ino`，标识文件的i节点号，可以通过`$ ls -li Makefile`查看对比；
* `st_mode`，位掩码，标识文件类型和指定文件权限；
    * bit[15:12], 文件类型；
    * bit[11:9]，`UGT`；
    * bit[8:0], `RWXRWXRWX`，分别表示文件属主（owner）、属组（group）以及其他用户（other）的读、写、执行权限；
* `st_nlink`，指向文件的硬链接数。
* `st_UID`，`st_GID`，表示文件的属主（UID）和属组（GID）；
* `st_rdev`，如果是设备文件，则包含设备的主、辅IDF；
* `st_size`，文件的字节总数；对于符号链接，则为链接所指路径名的长度；对于共享内存对象，则为对象大小；
* `st_blocks`，表示实际分配给文件的磁盘块数量。
* `st_blksize`，并非底层文件系统的块大小，而是文件系统上进行I/O操作的最优块大小。
* 文件时间戳
    * `st_atime`，文件的上次访问时间；
    * `st_mtime`，文件的上次修改时间；
    * `st_ctime`，文件的状态改变时间；

### st_mode 文件类型判断

    int mode = statval->st_mode;
    // 也可是使用宏定义，测试宏S_ISREG()
    if((mode & S_IFMT) == S_IFREG)
        printf("\t regular file\n");
    if(S_ISDIR(mode))
        printf("\t directory\n");
    if(S_ISCHR(mode))
        printf("\t char device\n");
    if(S_ISBLK(mode))
        printf("\t block device\n");
    if(S_ISFIFO(mode))
        printf("\t fifo/pipe file\n");
    if(S_ISSOCK(mode))
        printf("\t socket\n");
    if(S_ISLNK(mode))
        printf("\t link file\n");

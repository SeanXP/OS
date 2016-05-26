目录
====

目录的存储方式类似于普通文件，区别：

* 在其i-node条目，会将目录标记为一种不同的文件类型；（`stat()`中，返回的statbuf.st_mode中包含文件类型和权限，文件类型通过测试宏（如S_ISERG()、S_ISDIR()）判断。）
* 目录是经特殊组织而生成的文件。本质上是一个表格，包含文件名和i-node编号；

### mkdir -  create a directory

    #include <sys/stat.h>
    #include <sys/types.h>

    int mkdir(const char *pathname, mode_t mode);
`mkdir()`创建一个新目录`pathname`，若路径名已存在，则返回-1并设置errno为`EEXIST`。
`mode`参数决定新目录的权限。

### rmdir - delete a directory

    #include <unistd.h>

    int rmdir(const char *pathname);
    On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

rmdir() deletes a directory, which must be empty.

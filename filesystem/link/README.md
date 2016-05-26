链接 Link
====

i-node表的编号始于1，而非0，若目录条目的i-node字段值为0，则表明该条目尚未使用。
i-node 1 一般用来记录文件系统的坏块，而文件系统根目录（/）总是存储于i-node条目2中。因此，内核解析路径名就知道从哪里开始。

## 硬链接
linux下删除泄给文件，实质是将对应的i-node的链接计数减去1，只有当链接计数器减为0，才会删除（释放）文件的i-node记录和记录块。

    // 1. 创建新文件，分配新i-node记录和记录块。将i-node条目和文件名填写到目录的i-node表中；
    $ touch testfile

    // 2. 查看文件的i-node记录（系统调用stat()）
    $ ls -li testfile
    27002300 -rw-r--r-- 1 gxp users 0 May 26 15:30 testfile

    // 3. 建立硬链接，不会占用额外的i-node和数据，只是在目录中新加入一条目对应关系的数据。
    $ ln testfile linkfile

    // 4. 具有相同的i-node，指向相同的数据，链接计数器叠加至2；
    $ ls -li *file
    27002300 -rw-r--r-- 2 gxp users 0 May 26 15:30 linkfile
    27002300 -rw-r--r-- 2 gxp users 0 May 26 15:30 testfile

    // 5. 删除文件，链接计数器减一
    $ rm testfile; ls -li *file
    27002300 -rw-r--r-- 1 gxp users 0 May 26 15:30 linkfile

    // 6. 删除文件，链接计数器减为零，则释放此文件的i-node记录和记录块；
    $ rm linkfile
硬链接的限制（使用符号链接来加以规避）：

* 不同文件系统使用各自的i-node条目，因此硬链接必须和其指代的文件在同一文件系统，即硬链接不同跨文件系统，而软链接可以。
* 不能为目录创建硬链接，从而避免可能混乱的链接环路问题。

## 软链接

使用`ln -s source link`建立source文件的软链接；

    $ touch testfile
    $ ln -s testfile slinkfile
    $ ls -li *file
    27005694 lrwxrwxrwx 1 gxp users 8 May 26 15:41 slinkfile -> testfile
    27002300 -rw-r--r-- 1 gxp users 0 May 26 15:40 testfile
与硬链接不同，testfile与slinkfile使用不同的i-node，即软链接时会分配新的i-node节点。新i-node节点存储的数据是指向文件的名字，例如`testfile`，占用8个字节。

符号链接的内容既可以是绝对路径，也可以是相对路径，解释相对符号链接时以链接本身的位置为参考点。因为符号链接指代一个文件名，而非 i-node 编号，因此可以`跨不同文件系统来软链接文件`。
同时也可以为目录建立软链接。

大部分操作会无视符号链接的所有权和权限（所以符号链接文件一般权限都是777），是否允许操作是由其所指代的实际文件的所有权和权限来决定的。

    $ cat slinkfile
    hello world
    $ chmod 000 slinkfile
    $ ls -l *file
    lrwxrwxrwx 1 gxp users  8 May 26 15:41 slinkfile -> testfile
    ---------- 1 gxp users 12 May 26 15:49 testfile

## 创建和移除（硬）链接 - link & unlink
link - make a new name for a file

    #include <unistd.h>
    int link(const char *oldpath, const char *newpath);

link() creates a new link (also known as a hard link) to an existing file.
If newpath exists, it will not be overwritten.

unlink, unlinkat - delete a name and possibly the file it refers to

    #include <unistd.h>
    int unlink(const char *pathname);

unlink()  deletes a name from the filesystem.

* If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.
* If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring to
it is closed.
* If the name referred to a symbolic link, the link is removed.
* If the name referred to a socket, FIFO, or device, the name for it is removed but processes which have the object open may continue to use it.

## 创建软链接 - symlink
symlink — make a symbolic link relative to directory file descriptor

    #include <unistd.h>
    int symlink(const char *path1, const char *path2);

若路径名path2已存在，则调用失败返回-1并设置errno为EEXIST；

## 读取符号链接文件 - readlink

readlink - read value of a symbolic link

    #include <unistd.h>
    ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);
    Return number of bytes placed in buf on success, or -1 on error;
将符号链接文件的内容读取到buf中。

`read()`调用的参数如果是符号链接，则打开的是链接所指向的文件，而非链接文件本身。如果要打开链接文件本身，需要使用`readlink()`；

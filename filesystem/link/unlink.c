/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < unlink.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/26 >
  > Description:       文件硬链接

 unlink, unlinkat - delete a name and possibly the file it refers to

     #include <unistd.h>
     int unlink(const char *pathname);

    成功返回0，失败返回-1并设置errno.
    删除指定的文件项，如果文件对应的inode连接数目为0，且没有进程打开该文件，则释放该文件。

 unlink()  deletes a name from the filesystem.

 * If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.
 * If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring to
 it is closed.
 * If the name referred to a symbolic link, the link is removed.
 * If the name referred to a socket, FIFO, or device, the name for it is removed but processes which have the object open may continue to use it.

 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s link\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(unlink(argv[1]) == -1)
    {
        perror("unlink() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}

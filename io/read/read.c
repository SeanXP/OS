/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < read.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/12 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_MAX_LEN  1024
#define FILE_NAME1      "./hello.txt"

//readline()，利用系统函数read() 实现的函数readline()，读取文件中的一行内容，并返回读取的字节数。
int readline(int fd, char *buf, int nbytes);

int main(int argc, char* argv[])
{
    char buffer[BUFFER_MAX_LEN + 1];
    ssize_t ret;
    int fd;

    //{{{ read from stdio
    printf("STDIN_FILENO: %d\n", STDIN_FILENO);
    printf("Now, I am going to read string from stdin!\n");
    //ssize_t read(int fildes, void *buf, size_t nbyte);
    if((ret = read(STDIN_FILENO, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);
    //}}}
    //{{{ read from file
    // 如果read()从stdin读取，则遇到换行符`\n`，read()调用就结束。
    // 如果read()从文件读取，则遇到换行符`\n`不会结束。
    if((fd = open(FILE_NAME1, O_RDONLY)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    if((ret = read(fd, buffer, BUFFER_MAX_LEN)) < 0)
    {
        perror("read() error");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';     // read()不会在结尾添加'\0'，因此需要显式添加
    printf("I read %ld bytes.\n%s\n", ret, buffer);
    close(fd);
    //}}}
    //{{{ readline()
    if((fd = open(FILE_NAME1, O_RDONLY)) < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }
    ret = readline(fd, buffer, BUFFER_MAX_LEN);
    printf("I read %ld bytes.\n%s\n", ret, buffer);
    close(fd);
    //}}}

    return 0;
}
//{{{ readline()
//readline()，利用系统函数read() 实现的函数readline()，读取文件中的一行内容，并返回读取的字节数。
int readline(int fd, char *buf, int nbytes)
{
    int numread = 0; //读取的字节数目，用作索引量
    int returnval;   //返回值

    while(numread < nbytes - 1) //要读取nbytes个字节，且最后一个为换行符号，所以如果没有读到第nbytes - 1个字节，就继续执行循环。
    {
        returnval = read(fd, buf + numread, 1); //每次调用系统函数读取一个字节，然后判断
        //根据返回值进行判断
        if((returnval == -1) && (errno == EINTR)) //因为信号造成的终端
            continue;
        if((returnval == 0) && (numread == 0)) //空文件
            return 0;
        if(returnval == 0) //读到了文件结束符号，则跳出循环
            break;
        if(returnval == -1) //read函数发生错误，可查看errno
            return -1;

        //若没有执行上述条件语句，则说明为普通字符，正常读取即可。
        numread++;

        //判断是否读取换行符
        if(buf[numread-1] == '\n')
        {
            buf[numread] = '\0'; // It's over.
            return numread;
        }
    }

    //执行到这里，说明没有正常退出则返回-1并配置errno.
    errno = EINVAL;
    return -1;
}//}}}

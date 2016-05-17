/*************************************************************************
    > File Name: close_test.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月06日 星期三 15时26分18秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>  // void perror(const char * s);
#include<unistd.h> // int close(int fd);
// close() 成功返回0，失败返回-1并设置errno.
// errno = EBADF 表示fd是无效的
// errno = EINTR 表示close操作被信号终端. 详见single.

int main()
{
	int fd;

	if(close(fd) == -1)
		perror("Failed to close the file.[gxp]");
    return 0;
}


/*************************************************************************
  > File Name: buffer.c
  > Author: Shawn Guo
  > Mail: iseanxp@gmail.com
  > Created Time: 2013年11月06日 星期三 23时37分03秒
  > Last Changed:
  > Notes:
 *************************************************************************/

#include<stdio.h>

int main()
{
    //标准输出是行缓冲的，在缓冲区被填满或遇到换行符号前不会输出。
    fprintf(stdout, "a");
    //标准错误是不缓冲的，所以语句执行完后立刻显示出来。
    fprintf(stderr, "a has been written. ");
    fprintf(stdout, "b");
    fprintf(stderr, "b has been writeen. ");
    fprintf(stdout, "\n");

    return 0;
}


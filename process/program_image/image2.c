/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < image2.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/19 >
  > Description:
 ****************************************************************/

#include <stdio.h>

// 未初始化的静态变量，不占用磁盘空间，加载ELF时才会分配内存。
char myarray[100000];

int main(int argc, char* argv[])
{
    myarray[0] = 3;
    return 0;
}

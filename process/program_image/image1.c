/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < image1.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/19 >
  > Description:
 ****************************************************************/

#include <stdio.h>

// 已初始化的静态变量，将占用可执行文件的部分磁盘空间。
// 100k
char myarray[100000] = {1, 2, 3, 4};

int main(int argc, char* argv[])
{
    myarray[0] = 3;
    return 0;
}

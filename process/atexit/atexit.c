/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < atexit.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/03 >
  > Description:
              main函数执行return或执行到末尾或调用exit函数均表示正常终止。
              正常终止时可以调用用户定义的退出处理程序。
 ****************************************************************/

#include<stdio.h>
#include<stdlib.h>  // atexit();

// int atexit(void (*func) (void));
// 用户定义的退出处理程序，可以多次调用表示安装不同的处理程序。
// 后安装的程序在终止时先执行。

void func1()
{
    printf("This is func1 exit.\n");
}

void func2()
{
    printf("This is func2 exit.\n");
}

void func3()
{
    printf("This is func3 exit.\n");
}

int main(int argc, char* argv[])
{
    atexit(func1);
    atexit(func2);
    atexit(func3);

    return 0;
}

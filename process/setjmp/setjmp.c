/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < setjmp.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/19 >
  > Description:        non-local jumps, performing a nonlocal goto;
 ****************************************************************/

#include <stdio.h>
#include <setjmp.h>

static jmp_buf env;     // 保持进程相关信息，用于longjmp()跳转；

static void f2(void)
{
    longjmp(env, 2);
}

// 根据参数argc决定longjmp的参数为1还是2;
static void f1(int argc)
{
    if(argc == 1)
        longjmp(env, 1);
    else
        f2();
}

int main(int argc, char* argv[])
{
    switch(setjmp(env))
    {
        case 0:
            // 返回0，即setjmp()初次调用;
            printf("initial setjmp(), calling f1()...\n");
            f1(argc);   // Never return
            break;
        case 1:
            printf("jumped back from f1()\n");
            break;
        case 2:
            printf("jumped back from f2()\n");
            break;
    }
    return 0;
}

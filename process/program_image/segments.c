/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < segments.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/19 >
  > Description:        程序变量在进程内存各段的位置
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Uninitialized data segment
char globBuf[65535];
// Initialized data segment
int primes[] = { 2, 3, 5, 7 };

// Allocated in frame for square()
static int square(int x)
{
    int result; // Allocated in frame for square()

    result = x * x;
    return result;      // return value passed via register
}

// Allocated in frame for doCalc()
static void doCalc(int val)
{
    printf("The square of %d is %d\n", val, square(val));

    if(val < 1000)
    {
        int t;          // Allocated in frame for doCalc()

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

// Allocated in frame for main()
int main(int argc, char* argv[])
{
    static int key = 9973;          // Initialized data segment
    static char mbuf[10240000];     // Uninitialized data segment
    char *p;                        // Allocated in frame for main()

    p = malloc(1024);               // points to memory in heap segment

    doCalc(key);

    free(p);
    return 0;
}

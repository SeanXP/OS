#include<stdio.h>
#include<stdlib.h>

// char *getenv(const char *name);
// 读取参数name对应的环境变量的值，如果没有则返回NULL;

int main(int argc, char **argv)
{
    int i;

    for(i = 1; i < argc; i++)
    {
        printf("[%s] : %s\n", argv[i], getenv(argv[i]));
    }
    return 0;
}

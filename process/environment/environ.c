#include<stdio.h>

/* 进程开始执行的时候，外部变量environ指向进程环境列表。*/
extern char **environ;

int main()
{
    int i;

    printf("The environment list follows:\n");
    for(i = 0; environ[i] != NULL; i++)
        printf("environ[%d]: %s\n", i, environ[i]);

    return 0;
}

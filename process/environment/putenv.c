#include<stdio.h>
#include<stdlib.h>

// int putenv(char *string);
// Return 0 on success, or nonzero on error
// putenv()将environ变量中的某一元素指向参数string的地址，而非复制副本，因此当string被修改，将影响环境变量。

int main(int argc, char **argv)
{
    char buffer[] = "myname=seanxp";

    printf("env: \t\t[myname=%s]\n", getenv("myname"));
    printf("putenv: \t\t[myname=seanxp]\n");
    if(putenv(buffer) < 0)
    {
        perror("putenv() error\n");
        exit(EXIT_FAILURE);
    }
    printf("env: \t\t[myname=%s]\n", getenv("myname"));
    buffer[11] = 'X';
    printf("env: \t\t[myname=%s]\n", getenv("myname"));
    buffer[0] = 'M';
    printf("env: \t\t[myname=%s]\n", getenv("myname"));
    printf("env: \t\t[Myname=%s]\n", getenv("Myname"));

    // setput()
    printf("setenv()\n");
    if(setenv("yourname", "seanxp", 0) < 0)
    {
        perror("setenv() error.");
        exit(EXIT_FAILURE);
    }
    printf("env: \t\t[yourname=%s]\n", getenv("yourname"));
    printf("unsetenv()\n");
    if(unsetenv("yourname") < 0)
    {
        perror("unsetenv() error.");
        exit(EXIT_FAILURE);
    }
    printf("env: \t\t[yourname=%s]\n", getenv("yourname"));

    return 0;
}

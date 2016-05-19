/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < exec.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/03 >
  > Description:

#include <unistd.h>

extern char **environ;

int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg,
..., char * const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[],
char *const envp[]);
 ****************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    /*execv("/bin/ls", argv);*/
    /*execv("./hello", argv);*/

    //execvp()会从PATH 环境变量中查找符合参数file 的文件名, 找到后便执行该文件, 然后将第二个参数argv 传给该欲执行的文件。
    char * myargv[] = {"ls", "-al", "/etc/passwd", 0};
    execvp("ls", myargv);
    return 0;
}

/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < launch.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/03 >
  > Description:
 ****************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ARGS		64
#define	MAX_ARG_LEN		16
#define	MAX_LINE_LEN	80

#define	WHITESPACE		".,\t\n"


//如果定义MAIN_SAMPLE_MODE, 简单运行程序，创建5路子进程，显示pid后退出
//没有定义，则运行程序，创建5路子进程，并执行main参数文件里面的命令。用到execvp()
#define MAIN_SAMPLE_MODE


struct command_t {
    char	*name;
    int		argc;
    char	*argv[MAX_ARGS];
};


int parseCommand(char *cLine, struct command_t *cmd);


int main(int argc, char *argv[])
{

    int i;
    int pid, numchildren;
    int state;
    FILE *fid;
    char cmdline[MAX_LINE_LEN];
    struct command_t command;

    /* Read the command  line parameters */
    if(argc != 2)
    {
        fprintf(stderr, "Usage: launch <launch_set_filename>\n");
        exit(0);
    }

    fid = fopen(argv[1], "r");	// open a file that contains a set of commands.

    numchildren = 0;

    printf("The main process id is: %d\n", getpid());

    while(fgets(cmdline , MAX_LINE_LEN, fid) != NULL)
    {
        parseCommand(cmdline, &command);
        command.argv[command.argc] = NULL;


        // Create a child process to execute the command
        // fork() 产生一个新的进程。父进程执行完这句，fork()返回子进程的pid,
        // 子进程从下一句开始执行, fork()给子进程的pid返回0
        pid = fork();



        if(pid == 0)
        {
#ifdef MAIN_SAMPLE_MODE
            printf("This child process id is %d and father process id is %d \n", getpid(), getppid());
            exit(1);
#else

            //execvp()使得程序转而执行另外的程序，调用成功则不会返回，直接在另外的程序中exit退出。
            //所以execvp()函数下面到语句在execvp()调用成功后是不会执行的！
            execvp(command.name, command.argv);
#endif
        }

        numchildren++;
    }


    /* Terminate after all children have terminated */

    for(i = 0; i < numchildren; i++)
    {
        // 一旦调用wait()，就立刻阻塞自己，由wait自动分析当前进程的某个子进程是否已经退出
        // 如果调用进程没有子进程，则调用失败，wait返回-1
        // 如果找到已经变为僵尸进程的子进程，则wait收集子进程信息，彻底销毁并返回，如果没有找的，则一直阻塞。
        // wait()返回销毁子进程的pid.
        //
        pid = wait(&state);
        printf("PID: %d is over. \n", pid);

    }

    printf("\n\n launch: Launched %d commands \n", numchildren);
    printf("\n\n launch: Termination successfully. \n");

    return 0;
}


/* 将命令行字符串cLine由分割符WHITESPACE分割，放在cmd结构体中  */
int parseCommand(char *cLine, struct command_t *cmd)
{
    int argc = 0;
    char **clptr = 0;

    /* Initialization */
    clptr = &cLine;
    argc = 0;
    cmd->argv[argc] = (char *)malloc(MAX_ARG_LEN);

    /* Fill argv[] */

    while((cmd->argv[argc] = strsep(clptr, WHITESPACE)) != NULL)
    {
        cmd->argv[++argc] = (char *)malloc(MAX_ARG_LEN * sizeof(char));
    }

    /* Set the command name and argv */

    cmd->argc = argc - 1;
    cmd->name = (char *) malloc(sizeof(cmd->argv[0]));
    strcpy(cmd->name, cmd->argv[0]);

    return 1;
}


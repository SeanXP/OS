/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < mount.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/23 >
  > Description:        利用系统调用API mount() 实现简单版mount命令
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <getopt.h>

//{{{ usageError()
static void usageError(const char *progName, const char *msg)
{
    if(msg != NULL)
        fprintf(stderr, "%s", msg);

    fprintf(stderr, "Usage: %s [option] source target\n\n", progName);
    fprintf(stderr, "Available options:\n");
    fprintf(stderr, "\t -t fstype \t\t [e.g., 'ext2' or 'reiserfs']\n");
    fprintf(stderr, "\t -o data \t\t [file system dependent options, e.g., 'bsdgroups' for ext2]\n");
    fprintf(stderr, "\t -f mountflags \t\t can include any of:\n");
    fprintf(stderr, "\t\t b - MS_BIND \t\t create a bind mount\n");
    fprintf(stderr, "\t\t d - MS_DIRSYNC \t\t synchronous directory updates\n");
    fprintf(stderr, "\t\t l - MS_MANDLOCK \t\t permit mandatory locking\n");
    fprintf(stderr, "\t\t m - MS_MOVE \t\t atomically move subtree\n");
    fprintf(stderr, "\t\t A - MS_NOATIME \t\t don't update atime (last access time)\n");
    fprintf(stderr, "\t\t V - MS_NODEV \t\t don't permit device access\n");
    fprintf(stderr, "\t\t D - MS_NODIRATIME \t\t don't update atime on directories\n");
    fprintf(stderr, "\t\t E - MS_NOEXEC \t\t don't allow executables\n");
    fprintf(stderr, "\t\t S - MS_NOSUID \t\t disable set-user/group-ID programs\n");
    fprintf(stderr, "\t\t r - MS_RDONLY \t\t read-only mount\n");
    fprintf(stderr, "\t\t c - MS_REC \t\t recursive mount\n");
    fprintf(stderr, "\t\t R - MS_REMOUNT \t\t remount\n");
    fprintf(stderr, "\t\t s - MS_SYNCHRONOUS \t\t make writes synchronous\n");

    exit(EXIT_FAILURE);
}//}}}

int main(int argc, char* argv[])
{
    unsigned long flags = 0;
    char *data = NULL, *fstype = NULL;
    int j = 0, opt = 0;

    // use getopt() get parameter from shell
    while((opt = getopt(argc, argv, "o:t:f:")) != -1)
    {
        switch(opt)
        {
            case 'o':
                data = optarg;
                break;
            case 't':
                fstype = optarg;
                break;
            case 'f':
                for(j = 0; j < strlen(optarg); j++)
                {
                    switch(optarg[j])
                    {
                        case 'b': flags |= MS_BIND;         break;
                        case 'd': flags |= MS_DIRSYNC;      break;
                        case 'l': flags |= MS_MANDLOCK;     break;
                        case 'm': flags |= MS_MOVE;         break;
                        case 'A': flags |= MS_NOATIME;      break;
                        case 'V': flags |= MS_NODEV;        break;
                        case 'D': flags |= MS_NODIRATIME;   break;
                        case 'E': flags |= MS_NOEXEC;       break;
                        case 'S': flags |= MS_NOSUID;       break;
                        case 'r': flags |= MS_RDONLY;       break;
                        case 'c': flags |= MS_REC;          break;
                        case 'R': flags |= MS_REMOUNT;      break;
                        case 's': flags |= MS_SYNCHRONOUS;  break;
                        default: usageError(argv[0], NULL);
                    }
                }
                break;
            default:
                usageError(argv[0], NULL);
        }
    }
    if(argc != optind + 2)
        usageError(argv[0], "Wrong number of arguments\n");
    if(mount(argv[optind], argv[optind + 1], fstype, flags, data) == -1)
    {
        perror("mount() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}

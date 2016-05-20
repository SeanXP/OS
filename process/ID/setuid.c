/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < setuid.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/20 >
  > Description:        setegid, seteuid, setgid, setuid -- set user and group ID
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("uid = %d\n", getuid());
    printf("gid = %d\n", getgid());
    printf("euid = %d\n", geteuid());
    printf("egid = %d\n", getegid());

    // 1. 非特权进程（UID != 0）调用setuid()，仅能修改进程的EUID，且仅能将EUID修改为UID或save SUID；
    // 因此，对于非特权用户（非ROOT用户），当执行set-user-ID程序时（设置SUID权限位），setuid()才起作用；
    // 2. 特权进程，以非0参数调用setuid()时，UID、EUID、save SUID都将被设置！单向性操作，一旦设置，就失去了特权。

    printf("toggle EUID to UID, not SUID\n");
    // 这里配置可执行文件为owner:root, 设置SUID权限位，则euid = 0; 这里切换为UID；
    if(setuid(getuid()) == -1)
    {
        perror("setuid() error");
        exit(EXIT_FAILURE);
    }
    printf("euid = %d\n", geteuid());

    return 0;
}

/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < uname.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/23 >
  > Description:
    uname - get name and information about current kernel

    #include <sys/utsname.h>
    int uname(struct utsname *buf);

    uname() returns system information in the structure pointed to by buf.  The utsname struct is defined in <sys/utsname.h>:

    struct utsname {
        char sysname[];    // Operating system name (e.g., "Linux")
        char nodename[];   // Name within "some implementation-defined network"
        char release[];    // Operating system release (e.g., "2.6.28")
        char version[];    // Operating system version
        char machine[];    // Hardware identifier
    #ifdef _GNU_SOURCE
        char domainname[]; // NIS or YP domain name
    #endif
    };

    The length of the arrays in a struct utsname is unspecified (see NOTES); the fields are terminated by a null byte ('\0').

RETURN VALUE
    On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

ERRORS
    EFAULT buf is not valid.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
/*#define __GNU_SOURCE*/
#include <sys/utsname.h>

int main(int argc, char* argv[])
{
    struct utsname uts;
    if(uname(&uts) == -1)
    {
        perror("uname() error");
        exit(EXIT_FAILURE);
    }

    printf("Node name: \t\t %s\n",      uts.nodename);
    printf("System name: \t\t %s\n",    uts.sysname);
    printf("Release : \t\t %s\n",       uts.release);
    printf("Version: \t\t %s\n",        uts.version);
    printf("Machine: \t\t %s\n",        uts.machine);
#ifdef _GNU_SOURCE
    printf("Domain name: \t\t %s\n",    uts.domainname);
#endif

    return 0;
}

/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < getgrnam.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/20 >
  > Description:

    struct group * getgrnam(const char *name);
    struct group * getgrgid(gid_t gid);

           struct group {
                   char    *gr_name;       // group name
                   char    *gr_passwd;     // group password
                   gid_t   gr_gid;         // group id
                   char    **gr_mem;       // group members
           };
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <errno.h>

void print_group(struct group *gp)
{
    if(gp == NULL)
        return;
    printf("struct group of %s\n",  gp->gr_name);
    printf("\t gr_name: \t%s\n",    gp->gr_name);
    printf("\t gr_paswd: \t%s\n",   gp->gr_passwd);
    printf("\t gr_gid: \t%d\n",     gp->gr_gid);
    printf("\t gr_mem:\n");
    int i = 0;
    while(gp->gr_mem[i] != NULL)
    {
        printf("\t         \t%s\n", gp->gr_mem[i++]);
    }
}

int main(int argc, char* argv[])
{
    struct group *mygroup;

    if(argc > 1)
        mygroup = getgrnam(argv[1]);
    else
        mygroup = getgrnam("root");

    // 没有在passwd文件中发现匹配记录，则返回NULL，并设置errno为0;
    if(mygroup == NULL)
    {
        if(errno == 0)
            printf("Not found!\n");
        else
        {
            perror("getgrnam() error");
            exit(EXIT_FAILURE);
        }
    }
    print_group(mygroup);

    return 0;
}

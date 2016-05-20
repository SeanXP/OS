/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < getpwnam.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/20 >
  > Description:        getpwnam, getpwuid - password database operations

  struct passwd * getpwnam(const char *login);
  struct passwd * getpwuid(uid_t uid);
  Both return a pointer on success, or NULL on error;

    struct passwd {
          char    *pw_name;       // user name
          char    *pw_passwd;     // encrypted password
          uid_t   pw_uid;         // user uid
          gid_t   pw_gid;         // user gid
          time_t  pw_change;      // password change time
          char    *pw_class;      // user access class
          char    *pw_gecos;      // Honeywell login info
          char    *pw_dir;        // home directory
          char    *pw_shell;      // default shell
          time_t  pw_expire;      // account expiration
          int     pw_fields;      // internal: fields filled in
    };
The functions getpwnam(), getpwuid(), and getpwuuid() search the password database for the given login name, user uid, or user uuid respectively,
always returning the first one encountered.
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <errno.h>

void print_passwd(struct passwd *wd)
{
    if(wd == NULL)
        return;
    printf("struct passwd of %s\n", wd->pw_name);
    printf("\t pw_name: \t%s\n",    wd->pw_name);
    printf("\t pw_passwd: \t%s\n",  wd->pw_passwd);
    printf("\t pw_uid: \t%d\n",     wd->pw_uid);
    printf("\t pw_gid: \t%d\n",     wd->pw_gid);
    printf("\t pw_gecos: \t%s\n",   wd->pw_gecos);
    printf("\t pw_dir: \t%s\n",     wd->pw_dir);
    printf("\t pw_shell: \t%s\n",   wd->pw_shell);
}

int main(int argc, char* argv[])
{
    struct passwd *mypasswd;

    if(argc > 1)
        mypasswd = getpwnam(argv[1]);
    else
        mypasswd = getpwnam("root");

    // 没有在passwd文件中发现匹配记录，则返回NULL，并设置errno为0;
    if(mypasswd == NULL)
    {
        if(errno == 0)
            printf("Not found!\n");
        else
        {
            perror("getpwnam() error");
            exit(EXIT_FAILURE);
        }
    }
    print_passwd(mypasswd);

    return 0;
}

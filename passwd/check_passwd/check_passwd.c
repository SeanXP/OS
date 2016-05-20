/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < check_passwd.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/20 >
  > Description:
  char *getpass(const char *prompt);
        Return pointer to statically allocated input password string.
        屏蔽回显功能，停止对终端特殊字符的处理，打印参数prompt字符串，读取一行输入，返回以NULL结尾的输入字符串（静态分配）。
 ****************************************************************/

#define _XOPEN_SOURCE       // crypt()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // getpass(), sysconf(), crypt()
#include <pwd.h>
#include <errno.h>
#include <shadow.h>         // getspnam()

int main(int argc, char* argv[])
{
    char *username, *password, *encrypted, *p;
    struct passwd *pwd;
    struct spwd *spwd;
    int authOK;
    long lnmax;
    size_t len;

    // {{{ 1. get username
    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if(lnmax == -1)
        lnmax = 256;

    if((username = malloc(lnmax)) == NULL)
    {
        perror("malloc() error");
        exit(EXIT_FAILURE);
    }
    printf("Username: ");
    fflush(stdout);

    if(fgets(username, lnmax, stdin) == NULL)
    {
        exit(EXIT_FAILURE);
    }
    len = strlen(username);
    if(username[len - 1] == '\n')
        username[len - 1] = '\0';       // Remove trailing '\n';
    //}}}
    //{{{ 2. get password form /etc/passwd & /etc/shadow
    // get record form /etc/passwd
    if((pwd = getpwnam(username)) == NULL)
    {
        if(errno == 0)
            printf("Not found %s\n", username);
        else
            perror("getpwnam() error");
        exit(EXIT_FAILURE);
    }
    // get record form /etc/shadow
    if((spwd = getspnam(username)) == NULL)
    {
        if(errno == EACCES)
            perror("no permission to read shadow password file");
        else
            perror("getspnam() error");
        exit(EXIT_FAILURE);
    }
    pwd->pw_passwd = spwd->sp_pwdp; // use the shadow password
    //}}}
    // {{{ 3. get password and encrypt, then verify;
    // 读取密码后，应立即加密，并尽快将密码的明文从内存中抹去，以防恶意之徒借程序崩溃之机，读取内核转储文件以获取密码；
    password = getpass("Password: ");
    // Encrypt password and erase cleartext version immediately!!!
    encrypted = crypt(password, pwd->pw_passwd); // spwd->sp_pwdp为实际的加密密码，这里用来指示加密的盐；
    // 清除内存中的明文密码
    for(p = password; *p != '\0'; p++)
        *p++ = '\0';
    if(encrypted == NULL)
    {
        perror("crypt() error");
        exit(EXIT_FAILURE);
    }
    /*printf("sp_pwdp: %s\n", spwd->sp_pwdp);*/
    /*printf("encrypted:%s\n", encrypted);*/
    authOK = (strcmp(encrypted, pwd->pw_passwd) == 0);
    if(authOK == 0)
    {
        printf("Incorrect password\n");
        exit(EXIT_FAILURE);
    }
    printf("Successfully authenticated: UID=%ld\n", (long)pwd->pw_uid);
    //}}}
    // Now do authenticated work ...
    return 0;
}

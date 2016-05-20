user & group
====


## getpwnam, getpwuid - password database operations

    #include <sys/types.h>
    #include <pwd.h>
    #include <uuid/uuid.h>

    struct passwd * getpwnam(const char *login);
    struct passwd * getpwuid(uid_t uid);
    Both return a pointer on success, or NULL on error;

The functions getpwnam(), getpwuid(), and getpwuuid() search the password database for the given login name, user uid, or user uuid respectively,
always returning the first one encountered.

两者返回值相同，区别在于参数，`getpwnam()`的参数为登录名，`getpwuid()`的参数为UID；

返回：没有在passwd文件中发现匹配记录，则返回NULL，并设置errno为0;

返回的struct passwd为静态分配内存，故而`getpwnam()`与`getpwuid()`都是不可重入的。对应等价的一组可重入函数`getpwnam_r()`、`getpwuid_r()`等；

struct passwd结构体：

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

示例：

    struct passwd *mypasswd;

    if((mypasswd = getpwnam("root") == NULL)
    {
        if(errno == 0)
            printf("Not found\n");
        else
        {
            perror("getpwnam() error");
            exit(EXIT_FAILURE);
        }
    }

输出示例：

         pw_name:       root
         pw_passwd:     *
         pw_uid:        0
         pw_gid:        0
         pw_gecos:      System Administrator
         pw_dir:        /var/root
         pw_shell:      /bin/sh

## getgrnam, getgrgid - group database operations

    #include <grp.h>
    #include <uuid/uuid.h>

    struct group * getgrnam(const char *name);
    struct group * getgrgid(gid_t gid);

struct group结构体：

    struct group {
           char    *gr_name;       // group name
           char    *gr_passwd;     // group password
           gid_t   gr_gid;         // group id
           char    **gr_mem;       // group members
    };
## setpwent, getpwent, endpwent - 顺序扫描密码文件的记录

    #include <pwd.h>
    #include <uuid/uuid.h>

    void setpwent(void);
    struct passwd * getpwent(void);
        Return pointer on success, or NULL on end of stream or error;
    void endpwent(void);

* `getpwent()`从密码文件中逐条返回记录，当不再有记录（或出错）时返回NULL。
* `getpwent()`一经调用，会自动打开密码文件。当处理完毕，需调用`endpwent()`将其关闭；
* 调用`setpwent()`重返密码文件起始处。

.

    struct passwd *pwd;

    while((pwd = getpwent()) != NULL)
        printf("%-8s %5ld\n", pwd->pw_name, (long)pwd->pw_uid);
    endpwent();

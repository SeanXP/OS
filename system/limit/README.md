system limit
====

UNIX 要求，针对其所规范的每个限制，所有实现都必须支持一个最小值。

大多情况下，这些值都定义在`<limits.h>`头文件中，一般为`xxx_MAX`或`xxx_MIN`：

* `xxx_MAX`，代表对某类资源或特性的上限，且标准要求这些上限要具有一个确定的最小值。
* `xxx_MIN`，代表对某类资源或特性的下限。

为了程序的移植性，要保证程序在不同系统间都满足系统限制，通常为使用`<limits.h>`，并使用API`sysconf()`和`pathconf()`等；

系统限制归为3类：

* 运行时恒定值
    * 已经在`<limits.h>`中定义，为固定值；
    * `<limits.h>`中忽略其定义。
* 路径名变量值
    指与路径名（文件、目录、终端等）相关的限制，每个限制可能是相对于某个系统实现的常量，也可能随文件系统的不同而不同。
    在限制可能因路径名而变化的情况下，应该使用`pathconf()`或`fpathconf()`来获得此值。
    例如`NAME_MAX`限制是路径名变量值的一个例子，此限制定义了在一个特定的文件系统下文件名的最大长度：

        lim = pathconf(directory_path, _PC_NAME_MAX);

* 运行时可增加值
    指某一限制，相对于特定实现其值固定，且运行此实现的所有系统至少都应支持此最小值，然而，特定系统在运行时可能会增加该值，使用`sysconf()`获得系统所支持的实际值。

### Shell环境下获取系统限制 - getconf
getconf — get configuration values

    $ getconf ARG_MAX
    2097152

    $ getconf NAME_MAX /boot
    1530

    $ getconf NAME_MAX /
    255

* `ARG_MAX`, 提供给exec()的参数(argv)与环境变量(environ)所占存储空间的最大字节数；
* `NAME_MAX`，在一个特定的文件系统下文件名的最大长度；

### 程序中获取系统限制 - sysconf
sysconf - get configuration information at run time

    #include <unistd.h>

    long sysconf(int name);
    Returns value of limit specified by name, or -1 if limit is indeterminate or an error occurred.

参数`name`应是`<unistd.h>`文件中定义的`_SC_`系列常量之一，实际定义地点在`<bits/confname.h>`，例如`_SC_ARG_MAX`、`_SC_OPEN_MAX`、`_SC_PAGESIZE`等；

`<unistd.h>`内包含`<bits/confname.h>`头文件：

    /*  Get the `_PC_*' symbols for the NAME argument to `pathconf' and `fpathconf';
        the `_SC_*' symbols for the NAME argument to `sysconf';
        and the `_CS_*' symbols for the NAME argument to `confstr'.  */

    #include <bits/confname.h>

若无法确定某一限制，则函数返回-1；
若调用函数时发生错误，函数也返回-1，并设置errno为`EINVAL`，表示name无效；

### pathconf, fpathconf

    fpathconf, pathconf -- get configurable pathname variables

    #include <unistd.h>

    long fpathconf(int fildes, int name);

    long pathconf(const char *path, int name);
    Both return value of limit specified by name, or -1 if limit is indeterminate or an error occurred;

* `pathconf()`和`fpathconf()`之间的唯一区别在于对文件的指定方式。`pathconf()`采用路径名方式来指定，而`fpathconf()`采用（之前已经打开的）文件描述符；
* 参数`name`应该是`<unistd.h>`文件中定义的`_PC_`系列常量之一，实际定义地点在`<bits/confname.h>`，例如`_PC_LINK_MAX`、`_PC_PATH_MAX`、`_PC_NAME_MAX`等；



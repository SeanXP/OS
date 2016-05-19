environment list
====

新进程在创建时，会继承其父进程的环境副本。这是一种原始的进程间通信方式，环境提供了将信息传递给子进程的方法（单向，一次性），之后两者的环境变量可以各自更改而不影响。

### getenv - get an environment variable

    #include <stdlib.h>
    char *getenv(const char *name);

The getenv() function searches the environment list to find the environment variable name, and returns a pointer to the corresponding value string.

### environ

    extern char **environ;
C语言程序中，可以使用全局变量`char **environ`访问环境列表；C程序运行时，启动代码定义该变量并以环境列表地址为其赋值。
类似main()主函数的argv参数，由多个字符串数组构成，以NULL结尾。

### putenv - change or add an environment variable

    #include <stdlib.h>
    int putenv(char *string);

    Return 0 on success, or nonzero on error;
putenv()将environ变量中的某一元素指向参数string的地址，而非复制副本，因此当string被修改，将影响环境变量。

    char buffer[] = "myname=seanxp";
    putenv(buffer);
    buffer[11] = 'X';
    getenv("myname");   // return "seanXp"
    buffer[0] \= 'M';
    getenv("myname");   // return null
    getenv("Myname");   // return "seanXp"

### setenv - change or add an environment variable

    #include <stdlib.h>

    int setenv(const char *name, const char *value, int overwrite);
    Return 0 on success, or -1 on error;
setenv()可以代替putenv()添加或修改环境变量，setenv()会根据参数`name`与`value`，分配一块内存缓冲区并构造形如`name=value`的字符串，以此来创建一个新的环境变量。
`overwrite`参数如果非0，则当`name`变量的环境变量已存在时，则使用`value`覆盖其值；

    int unsetenv(const char name);
    Return 0 on success, or -1 on error;

unsetenv()用于移除某环境变量。

### clearenv - clear the environment
The  clearenv()  function clears the environment of all name-value pairs and sets the value of the external variable environ to NULL.
clearenv函数不是POSIX标准制定的，所以如果clearenv在你的系统上没有，也可以直接设置`environ = NULL;`来达到相同的目的。

    #include <stdlib.h>
    int clearenv(void);
    Returns 0 on success, or a nonzero value on failure.
使用setenv()所分配的一块内存缓冲区，随之成为进程环境的一部分，而调用clearenv()则没有释放缓冲区，导致内存泄漏。

non-local jumps
====
performing a nonlocal goto;

使用库函数`setjmp()`和`longjmp()`可执行非局部跳转（nonlocal goto）。非局部，指跳转的目标为当前执行函数之外的某位置。

**不要使用goto，尽量不要使用setjmp() & longjmp()**

### goto 语句的限制

C语言的goto语句存在一个限制，即不能从当前函数跳转到另一函数。而非局部跳转提供这一功能。

### setjmp

    #include <setjmp.h>

    int setjmp(jmp_buf env);
    int sigsetjmp(sigjmp_buf env, int savesigs);
    Return 0 on initial call, nonzero on return via longjmp();
`setjmp()`调用为后续`longjmp()`调用执行的跳转确立了跳转目标。从编程角度，调用`longjmp()`函数后，看起来就和第二次调用`setjmp()`返回时完全一样。
通过查看`setjmp()`返回的整型值，可以区分`setjmp()`调用是初次返回还是第二次“返回”。

初始调用返回0，后续“伪”调用返回的值为`longjmp()`调用中val参数所致的任意值；通过val参数的值，可以区分程序跳转至同一目标的不同起跳位置。

env参数为成功实现跳转提供辅助，`setjmp()`把当前进程环境的各种信息保存到env参数中，调用`longjmp()`时必须指定相同的env，以此来执行“伪”返回；

### longjmp

    void longjmp(jmp_buf env, int val);
    void siglongjmp(sigjmp_buf env, int val);

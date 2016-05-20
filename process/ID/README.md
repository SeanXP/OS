进程凭证
====
每个进程都有一套数字表示的用户ID（UID）和组ID（GID），称为进程凭证（process credential）。

* 实际用户ID（real user ID）、实际组ID（real group ID）
* 有效用户ID（effective user ID）、有效组ID（effective group ID）
* 保存的ser-user-ID（saved set-user-ID）、保存的set-group-ID（saved set-group-ID）
* 文件系统用户ID（file-system user ID）、文件系统组ID（file-system group ID）
* 辅助组ID

## real user/group ID - UID/GID
确定进程所属的用户和组。

* 登录SHELL进程从/etc/passwd文件中读取密码记录的第三、四字段，获得UID与GID；
* 其他子进程从父进程中继承UID与GID；

## effective user/group ID - EUID/EGID
进程用来决定我们对资源的访问权限。一般情况下，有效用户ID等于实际用户ID，有效用户组ID等于实际用户组ID。

EUID为0的进程拥有ROOT权限，称为特权级进程（privileged process）。
## set-user/group-ID - SUID/SGID
SUID程序会将进程的EUID设置为可执行文件的UID（属主），从而获得常规情况下并不具有的权限。

    $ ls -l /usr/bin/passwd
    -rwsr-xr-x 1 root root 47K Mar 15  2015 /usr/bin/passwd

    $ ls -l `which mount`                                                                                                                                                 !845
    -rwsr-xr-x 1 root root 40208 Apr 12 20:12 /usr/bin/mount

    $ ls -l `which mount`                                                                                                                                                 !845
    -rwsr-xr-x 1 root root 40208 Apr 12 20:12 /usr/bin/mount

    $ ls -l `which wall`                                                                                                                                                  !848
    -rwxr-sr-x 1 root tty 27424 Apr 12 20:12 /usr/bin/wall

可以通过以下命令添加可执行文件的SUID、SGID权限位：

    $ chmod u+s xxx.elf
    $ chmod g+s xxx.elf

当运行SUID程序时，内核会将进程的EUID设置为可执行文件的UID。SGID同理。使得进程获得常规情况下所不具有的权限。

常用的用法是给一个属主为ROOT的程序设置SUID，例如`/usr/bin/passwd`，普通用户执行该程序时，进程的EUID为ROOT，可以修改`/etc/passwd`文件。而普通用户对`/etc/passwd`没有写的权限，不能直接写，只有通过`/user/bin/passwd`程序来修改自己的密码。

在Linux系统中，给shell脚本设置SUID权限位或SGID权限位是无效的。

## save set-user/group-ID
保存SUID和保存SGID，意在与SUID和SGID结合使用。

当执行程序时，将会（依次）发生如下事件：

* 若可执行文件的SUID权限位已开启，则设置进程的EUID为可执行文件的owner；若未设置SUID权限位，则EUID不变，与UID相同。
* 保存SUID和保存SGID的值由对应的EUID、EGID复制而来。无论是否设置权限位，这一复制都将进行。

不少系统调用，允许将SUID程序的EUID在UID和save SUID之间切换。程序可以游走于两种状态：具备获得特权的潜力（EUID = UID）和以特权进行实际操作（EUID = save SUID）。

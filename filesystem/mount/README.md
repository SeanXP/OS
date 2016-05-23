mount
====

系统调用`mount()`与`umount()`运行特权级进程（CAP_SYS_ADMIN）以挂载或卸载文件系统。

* 通过Linux专有的虚拟文件`/proc/mounts`，可查看当前已挂载文件系统的列表。`/proc/mounts`是内核数据结果的接口，因此包含已挂载文件系统的精确信息。
* `mount(8)`和`umount(8)`命令会自动维护`/etc/mtab`文件，该文件与`/proc/mounts`类似，或者就是`/proc/mounts`的符号链接。
* `/etc/fstab`文件（由系统管理员手工维护）包含了对系统支持的所有文件系统的描述，供`mount(8)`、`umount(8)`以及`fsck(8)`命令所使用。

### mount - mount a filesystem

    #include <sys/mount.h>

    int mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data);

    Returns 0 on success, or -1 on error;

* 将`source`设备所包含的文件系统，挂载到`target`指定的目录下；
* `filesystemtype`，用来标识`source`设备所含文件系统的类型，例如`ext4`或`exfat`等；
* `mountflags`，为标志位掩码，用来修改mount操作；
* `data`是一个指向信息缓冲区的指针，对其信息的解释则取决于文件系统。

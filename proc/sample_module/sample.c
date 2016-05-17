/*************************************************************************
    > File Name: sample.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月30日 星期六 22时33分17秒
    > Last Changed: 
    > Notes:	示例代码,学习/proc虚拟文件系统的编程方法
*************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/sched.h>
#include<linux/uaccess.h>

#define	STRINGLEN 1024


char global_buffer[STRINGLEN];	//分配一块大小为1024字节的内存

struct proc_dir_entry *example_dir, *hello_file, *current_file, *symlink;

//xuehao_dir为以自己学号创建的目录, xing_file为只读的文件,显示当前进程的PID
//ming_file是可读写的,写入的字符串将一直存储，可以查看.
struct proc_dir_entry *xuehao_dir, *xing_file, *ming_file;

int proc_read_current(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	//用户读取current文件时,内核调用这个函数
	int len;

	try_module_get (THIS_MODULE);	//模块引用计数增加1,保证模块不会被卸载
	//打印当前进程的名字和pid
	len = sprintf(page, "cunt process usages: \n name: %s \n pid: %d\n",
					current->comm, current->pid);
	module_put (THIS_MODULE);		//模块引用计数减1

	return len;
}

int proc_read_xing(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	//用户读取xing_file文件时,内核调用这个函数
	int len;

	try_module_get (THIS_MODULE);	//模块引用计数增加1,保证模块不会被卸载
	//打印当前进程的名字和pid
	len = sprintf(page, "current process Info:\nName: %s\n pid: %d\n",
					current->comm, current->pid);

	module_put (THIS_MODULE);		//模块引用计数减1

	return len;
}

int proc_read_hello(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	//用户读取hello文件时,内核调用这个函数
	int len;

	try_module_get (THIS_MODULE);	//模块引用计数增加1,保证模块不会被卸载

	//当前进程的名字以及global_buffer的内容，作为用户读出的内容
	len = sprintf(page, "hello message:%s\nwrite:%s\n",
					current->comm, global_buffer);

	module_put (THIS_MODULE);		//模块引用计数减1

	return len;

}

int proc_write_hello(struct file *file, const char *buffer, unsigned long count, void *data)
{
	//用户写hello文件时,内核将调用这个函数
	int len;

	try_module_get (THIS_MODULE);

	if(count >= STRINGLEN)	//如果写的内容超过1024,则截断
		len = STRINGLEN - 1;
	else
		len = count;

	//从用户的缓冲区获得要写的数据
	copy_from_user (global_buffer, buffer, len);
	global_buffer[len] = '\0';
	module_put (THIS_MODULE);

	return len;
}

int proc_read_ming(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	//用户读取ming_file文件时,内核调用这个函数
	int len;

	try_module_get (THIS_MODULE);	//模块引用计数增加1,保证模块不会被卸载

	//当前进程的名字以及global_buffer的内容，作为用户读出的内容
	len = sprintf(page, "current Command:%s\nGlobal String:%s\n",
					current->comm, global_buffer);

	module_put (THIS_MODULE);		//模块引用计数减1

	return len;

}

int proc_write_ming(struct file *file, const char *buffer, unsigned long count, void *data)
{
	//用户写ming_file文件时,内核将调用这个函数
	int len;

	try_module_get (THIS_MODULE);

	if(count >= STRINGLEN)	//如果写的内容超过1024,则截断
		len = STRINGLEN - 1;
	else
		len = count;

	//从用户的缓冲区获得要写的数据
	copy_from_user (global_buffer, buffer, len);
	global_buffer[len] = '\0';
	module_put (THIS_MODULE);

	return len;
}

static int init(void)
{
	//将会在加载模块的时候被调用, 创建proc文件

	example_dir = proc_mkdir("proc_test", NULL);	//在/proc目录下创建目录 pro_test/

	//创建只读文件 /proc/pro_test/current
	//struct proc_dir_entry *create_proc_read_entry 
	//(const char *name,mode_t mode,struct proc_dir_entry *base,read_proc_t *read_proc,void *data);
	//		名字，权限，位置，只读函数,data.
	current_file = create_proc_read_entry("current", 0666, example_dir, proc_read_current, NULL);

	//创建一个可读写的文件/proc/proc_test/hello
	hello_file = create_proc_entry ("hello", 0644, example_dir);
	strcpy( global_buffer, "hello string");
	//可以另行配置proc_dir_entry数据结构中其他成员.
	hello_file->read_proc = proc_read_hello;
	hello_file->write_proc = proc_write_hello;

	//创建一个链接 current_too 指向current.
	symlink = proc_symlink("current_too", example_dir, "current");


	//-----------------------

	xuehao_dir = proc_mkdir("12345678", NULL);	//在/proc目录下创建目录
	xing_file = create_proc_read_entry("hello", 0440, xuehao_dir, proc_read_xing, NULL);
	ming_file = create_proc_entry ("world", 0660, xuehao_dir);
	strcpy( global_buffer, "global string");
	ming_file->read_proc = proc_read_ming;
	ming_file->write_proc = proc_write_ming;


	return 0;
}

static void exit(void)
{
	remove_proc_entry ("current_too", example_dir);
	remove_proc_entry ("hello", example_dir);
	remove_proc_entry ("current", example_dir);
	remove_proc_entry ("proc_test", NULL);


	remove_proc_entry ("hello", xuehao_dir);
	remove_proc_entry ("world", xuehao_dir);
	remove_proc_entry ("12345678", NULL);
}

module_init(init);
module_exit(exit);

MODULE_LICENSE("DUAL BSD/GPL");          //告诉内核模块的版权信息/许可权限

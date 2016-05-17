/*************************************************************************
    > File Name: bookname.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11/18
    > Last Changed: 
    > Notes:编写一个内核模块bookname, 演示带参数的内核模块用法
	>		可以使用lsmod命令显示模块信息,可以用rmmod命令删除该模块. 
	>		lsmod / insmod / rmmod
	>		dmesg可查看从内核发出的消息.
*************************************************************************/

#include<linux/init.h>
#include<linux/module.h>                 //包含对模块的结构定义以及模块的版本控制.
#include<linux/kernel.h>
MODULE_LICENSE("DUAL BSD/GPL");          //告诉内核模块的版权信息/许可权限

static char *book_name = "dissecting Linux Device Driver";
static int book_num = 4000;

MODULE_PARM_DESC(book_name,"Book's name.");
MODULE_PARM_DESC(book_num, "Book's number.");

module_param(book_num, int, S_IRUGO); //添加内核模块参数 [参数名，参数类型，读/写权限] 
module_param(book_name, charp, S_IRUGO);

static int book_init(void)				//参数为空但是没有void时，编译会警告
{
	printk(KERN_INFO " Book name:%s\n", book_name);
	printk(KERN_INFO " Book num: %d\n", book_num);

	return 0;
}

static void book_exit(void)                //参数为空但是没有void时，编译会警告
{
	printk(KERN_ALERT "Book module exit \n");
}

module_init(book_init); //模块注册
module_exit(book_exit);

MODULE_AUTHOR("Shawn Guo");
MODULE_DESCRIPTION("A simple Book Module");
MODULE_ALIAS("simplest book module"); //别名
MODULE_VERSION("V1.0");


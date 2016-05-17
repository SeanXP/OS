/*************************************************************************
    > File Name: chr_dev.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月27日 星期三 20时17分16秒
    > Last Changed: 
    > Notes:	字符驱动程序 
*************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>		// struct file_operations;
#include<linux/cdev.h>		//包含字符驱动设备struct cdev的定义;
/********************** <linux/cdev.h> *******************
   strut cdev{
	struct kobject kobj;				//内嵌的内核对象
	struct module *owner;				//指向内核模块对象的指针
	const struct file_operations *ops;	//应用程序调用操作系统接口呼叫到设备驱动程序中的相应操作
	struct list_head list;				//链表
	dev_t dev;							//字符设备的设备号
	unsigned int count;					//次设备号的个数
   };
**********************************************************/


static struct cdev chr_dev;	//定义一个字符设备对象
static dev_t ndev;			//字符设备节点的设备号

static int chr_open(struct inode *nd, struct file *filp)
{
	int major = MAJOR(nd->i_rdev); //利用MAJOR & MINOR宏操作得到设备的主设备号及次设备号
	int minor = MINOR(nd->i_rdev);

	//这里不进行打开操作, 只打印一条内核信息.
	printk("chr_open(): major=%d,minor=%d\n", major, minor);

	return 0;
}

static ssize_t chr_read(struct file *f, char __user *u, size_t sz, loff_t *off)
{
	printk("In the chr_read() function!\n");

	return 0;
}


//字符设备驱动程序中一个非常关键的数据结构
struct file_operations chr_ops =
{
	.owner = THIS_MODULE,	//THIS_MODULE是指向当前内核模块对象的指针, owner成员避免在
							//调用file_operations的函数时,所属模块被卸载.
	.open = chr_open,
	.read = chr_read,
};

static int chr_init(void)
{
	int ret; //用于存放函数调用返回值的变量

	cdev_init(&chr_dev, &chr_ops);	//调用函数初始化字符设备对象

	ret = alloc_chrdev_region(&ndev, 0, 1, "chr_dev");	//自动分配设备号
	
	if(ret < 0)	//分配失败则返回负值
		return ret;

	printk("chr_init(): major=%d,minor=%d\n", MAJOR(ndev), MINOR(ndev));

	ret = cdev_add(&chr_dev, ndev, 1);		//将对应的字符设备对象chr_dev注册进系统
	//调用cdev_add把字符设备对象指针嵌入一个struct probe节点中，并将该节点加入
	//cdev_map所实现的哈希链表中. cdev_add 对应 cdev_del函数.
	
	if(ret < 0)//注册失败
		return ret;

	return 0;
}

static void chr_exit(void)
{
	printk("chr_exit(): Removing chr_dev module...\n");
	cdev_del(&chr_dev);	//注销chr_dev对应的字符设备对象
	unregister_chrdev_region(ndev, 1);		//释放分配的设备号
}

module_init(chr_init);
module_exit(chr_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shawn Guo @ Xidian University");
MODULE_DESCRIPTION("A char device driver as an example.");

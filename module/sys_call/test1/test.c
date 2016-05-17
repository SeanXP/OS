/*************************************************************************
  > File Name: test.c
  > Author: Shawn Guo
  > Mail: iseanxp@gmail.com 
  > Created Time: 2013年11月24日 星期日 13时11分15秒
  > Last Changed: 
  > Notes: 
 *************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>

void **sys_call_table;

asmlinkage int (*original_call) (const char*, int, int);

asmlinkage int our_sys_open(const char* file, int flags, int mode)
{
	printk("A file was opened\n");
	return original_call(file, flags, mode);
}

static int __init init_module(void)
{
	// sys_call_table address in System.map

	sys_call_table = (void*)0xc15ee0a0;
	original_call = sys_call_table[__NR_open];

	// Hook: Crashes here
	sys_call_table[__NR_open] = our_sys_open;
}

static void __exit cleanup_module(void)
{
	// Restore the original call
	sys_call_table[__NR_open] = original_call;
}

module_init(init_module);
module_exit(cleanup_module);

MODULE_LICENSE("DUAL BSD/GPL");
MODULE_AUTHOR("Shawn Guo");
MOULE_DESCRIPTION("Add sys_call by kernel module.");
MODULE_ALIAS("add sys_call");


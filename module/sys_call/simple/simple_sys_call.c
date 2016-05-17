/*************************************************************************
  > File Name: simple_sys_call.c
  > Author: Shawn Guo
  > Mail: iseanxp@gmail.com 
  > Created Time: 2013年11月24日 星期日 00时38分33秒
  > Last Changed: 
  > Notes: 
 *************************************************************************/

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/unistd.h>

#include<linux/time.h>

#include<asm/uaccess.h> // for copy_to_user
#include<linux/sched.h> // for current macro

#define __NR_pedagogictime 233

static int (*saved)(void);

static int sys_pedagogictime(struct timeval *tv)
{
	struct timeval ktv;
	do_gettimeofday(&ktv);
	copy_to_user(tv,&ktv,sizeof(ktv));
	printk(KERN_ALERT"PID %ld called sys_gettimeofday().\n",(long)current->pid);
	return 0;
}

int syscall(void)
{
	long *systable;	//用于保存系统调用表
	systable=(long*);
	saved=(int(*)(void))(systable[__NR_pedagogictime]);
	systable[__NR_pedagogictime]=(unsigned long)sys_pedagogictime;
	return 0;
}

void exit_syscall(void)
{
	unsigned long *systable;
	systable=( long*)0xc02b2600;
	systable[__NR_pedagogictime]=(unsigned long)saved;
}

module_init(syscall);
module_exit(exit_syscall);

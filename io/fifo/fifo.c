/*************************************************************************
    > File Name: fifo.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月10日 星期日 15时38分03秒
    > Last Changed: 
    > Notes: FIFO命名管道练习
	>		 创建一个FIFO管道，fork一个子进程，子进程想管道输出字符
	>		 父进程进行读取并显示

	管道可以实现一个程序内, 或者父子进程之间的通信。但是对于非父子的不同进程之间，
	彼此的文件描述符是不同的(不像父子进程, 子进程继承了父进程通过pipe()创建的管道)，
	则无法使用管道通信。
	而FIFO命名管道，则可以实现非父子进程间的通信。
	
	命名管道与路径名相关连，但是仅仅是命名，便于不同进程引用特定的管道。
	文件名对应的文件中是没有数据的。这种使用真实文件作为不同进程间的桥梁的思想, 
	还可以参考IPC中的IPC键的指定(ftok()函数);

	创建的命名管道独立于程序, 即程序结束后命名管道文件不会消失, 需要自行删除.
	命名管道的读写需要是阻塞形式的.
*************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>

#define	BUFSIZE		256
#define	FIFO_PERM	(S_IRUSR | S_IWUSR)		//预设的FIFO管道模式


int Dofifo_child(const char *fifo_name, const char *idstring); //子进程向管道写入字符串idstring
int Dofifo_parent(const char *fifo_name);					   //父进程从管道中进行读取并显示

int main()
{
	pid_t child_pid;
	const char fifo_name[] = "myfifo";	//将要创建的命名管道->myfifo.

	//make a fifo file.
	if(mkfifo(fifo_name, FIFO_PERM) == -1)
	{
		if(errno != EEXIST) //errno == EEXIST表示命名管道已存在，则程序可以继续执行。
		{
			//errno != EEXIST, 则程序无法创建命名管道且不存在该管道, 程序结束.
			fprintf(stderr, "[PID:%ld]: failed to create the named pipe.\n", (long)getpid());
			return -1;
		}
	}

	// fork a new process.
	if((child_pid = fork()) == -1)
	{
		perror("Failed to fork");
		return -1;
	}
	else if(child_pid == 0)
	{
		// child process write a string to this fifo file.
		return Dofifo_child(fifo_name, "this was written by the child.");
	}
	else
		// father process read strings from this fifo file.
		return Dofifo_parent(fifo_name);

    return 0;
}

int Dofifo_child(const char *fifo_name, const char *idstring) //子进程向管道写入字符串idstring
{
	char buf[BUFSIZE];
	int fd;
	int rval;
	ssize_t str_size;

	fprintf(stderr, "[PID:%ld]:(child) ready to open FIFO %s...\n", (long)getpid(), fifo_name);

	//像正常文件一样打开FIFO文件
	//这里如果打开失败且失败原因为信号中断，则继续打开操作
	while(((fd = open(fifo_name, O_WRONLY)) == -1) && (errno == EINTR))
		fprintf(stderr, "child is trying to open fifo file...\n");

	if(fd == -1)
	{
		//打开失败
		fprintf(stderr, "[PID:%ld]:Failed to open named pipe %s for write:%s\n", (long)getpid(), 
				fifo_name, strerror(errno));
		return -1;
	}
	//  到这一步，说明成功打开文件,接下来先将字符串写入缓存数组
	//	snprintf()函数写入时不会超过指定的长度，且可以插入一个空字符来终止.
	rval = snprintf(buf, BUFSIZE, "[PID:%ld]:%s]", (long)getpid(), idstring);
	if(rval < 0)
	{
		//字符串写入缓存数组失败
		fprintf(stderr, "[PID:%ld]: Failed to make the string:\n", (long)getpid());
		return -1;
	}

	str_size = strlen(buf) + 1;
	fprintf(stderr, "[PID:%ld]:ready to write...\n",(long)getpid());

	//写入字符串至FIFO通道文件
	rval = write(fd, buf, str_size);

	if(rval != str_size)
	{
		//没有写成功
		fprintf(stderr, "[PID:%ld]:Failed to write to FIFO file %s\n",
				(long)getpid(), strerror(errno));
		return -1;
	}

	fprintf(stderr, "[PID:%ld]: write string...finishing...\n", (long)getpid());
	
	return 0;
}



int Dofifo_parent(const char *fifo_name)					   //父进程从管道中进行读取并显示
{
	char buf[BUFSIZE];
	int fd;
	int rval;

	fprintf(stderr, "[PID:%ld]:(parent) ready to open FIFO %s...\n",
			(long)getpid(), fifo_name);

	// open the named pipe
	while(((fd = open(fifo_name, O_RDONLY)) == -1) && (errno == EINTR))
		fprintf(stderr, "parent is trying to open fifo file...\n");

	if(fd == -1)
	{
		// Fail to open fifo file 
		fprintf(stderr, "[PID:%ld]:Failed to open named pipe %s for read:%s\n",
				(long)getpid(), fifo_name, strerror(errno));
		return -1;
	}

	fprintf(stderr, "[PID:%ld]:ready to read...\n", (long)getpid());
	
	// read string from FIFO file.
	rval = read(fd, buf, BUFSIZE);
	if(rval == -1)
	{
		// Failed to read
		fprintf(stderr, "[PID:%ld]:Faild to read from pipe:%s\n",
				(long)getpid(), strerror(errno));
		return -1;
	}

	fprintf(stderr, "[PID:%ld]:read {%.*s} from FIFO.\n",
			(long)getpid(), rval, buf);
	return 0;
}


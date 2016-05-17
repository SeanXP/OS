/*************************************************************************
    > File Name: simple_ring.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年11月16日 星期六 22时14分10秒
    > Last Changed: 
    > Notes:	单个进程成环，即将进程的标准输出连接到标准输入 
*************************************************************************/

#include<stdio.h>
#include<unistd.h>


int main()
{
	int fd[2];

	pipe(fd);
	dup2(fd[0], STDIN_FILENO); //将fd[0]拷贝到标准输入对应的文件描述符表中
	dup2(fd[1], STDOUT_FILENO);

	//执行到这里，由两个环，一个是通道fd[1] -> fd[0];
	//另一个是 STDOUT_FILENO -> STDIN_FILENO;

	close(fd[0]);
	close(fd[1]); 
	//虽然关闭了管道，但stdout和stdin仍相连，也算一个管道.
	
	{
		int i, myint;
		for(i = 0; i < 10; i++)
		{
			//在stdout输出i,就可以在stdin中读取出i
			write(STDOUT_FILENO, &i, sizeof(i));
			read(STDIN_FILENO, &myint, sizeof(myint));
			fprintf(stderr,"%d\n",myint);
		}
	}


    return 0;
}


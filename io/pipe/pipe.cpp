#include <unistd.h>
#include <iostream>

using namespace std;
int main(int argc,char **argv)
{
	int pipe1[2],pipe2[2];
	char pstr[]="parent data";
	char cstr[]="child data";
	char buf[100];

	if(pipe(pipe1) < 0 || pipe(pipe2) < 0)
		cout<<"pipe error"<<endl;
	printf("create two pipe,pipe1: %d,%d; pipe2: %d,%d;\n",pipe1[0], pipe1[1], pipe2[0], pipe2[1]);

	pid_t pid=fork();
	if(pid>0)
	{
		//父进程,用管道1写数据,管道2读数据
		close(pipe1[0]);//关闭pipe1读端口
		close(pipe2[1]);//关闭pipe2写端口

		//父进程先发送数据, 然后等待接收.
		write(pipe1[1],pstr,sizeof(pstr));
		if(read(pipe2[0],buf,100)>0)
			cout<<"parent received:"<<buf<<endl;
	}	
	else if(pid==0)
	{
		//子进程用管道1读数据,管道2写数据
		close(pipe1[1]);//关闭pipe1写端口
		close(pipe2[0]);//关闭pipe2读端口

		//子进程先接收父进程发送的数据，然后应答父进程.
		if(read(pipe1[0],buf,100)>0)
			cout<<"child received:"<<buf<<endl;
		write(pipe2[1],cstr,sizeof(cstr));
		exit(0);
	}
	else
		cout<<"fork error"<<endl;
	return 0;
}


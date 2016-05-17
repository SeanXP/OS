/*************************************************************************
    > File Name: posix_file.c
    > Author: Shawn Guo
    > Mail: iseanxp@gmail.com 
    > Created Time: 2013年09月13日 星期五 07时32分54秒
    > Last Changed: 
    > Notes: 
*************************************************************************/

#include<stdio.h>
#include<fcntl.h>

int main()
{
	int infile, outfile;
	char *infilename = "in_test", *outfilename = "out_test";
	int len = 0;
	char c;

	// open, 调用成功返回一个无符号的整数描述文件，返回值用于标识打开的文件
	// O_RDONLY		O_WRONLY		O_RDWR等，还有其他flags
	infile = open(infilename, O_RDONLY);
	outfile = open(outfilename, O_WRONLY);

	/* Loop thougn the input file */
	while((len = read(infile, &c, 1)) > 0)
		write(outfile, &c, 1);

	close(infile);
	close(outfile);

    return 0;
}


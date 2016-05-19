program image
====

可执行文件被操作系统加载以后，在内存中占的连续内存为**程序映像(program image)**。

其中，已初始化的静态数据和未初始化的静态数据存放的地址不同。

* 已初始化的静态数据是可执行文件的一部分，占可执行文件的磁盘空间的一部分。
* 未初始化的静态数据只有在可执行文件加载时才会被分配相应的内存，不占磁盘空间。

----

`image1.c`

    #include <stdio.h>

    // 已初始化的静态变量，将占用可执行文件的部分磁盘空间。
    // 100k
    char myarray[100000] = {1, 2, 3, 4};

    int main(int argc, char* argv[])
    {
        myarray[0] = 3;
        return 0;
    }

`image2.c`

    #include <stdio.h>

    // 未初始化的静态变量，不占用磁盘空间，加载ELF时才会分配内存。
    char myarray[100000];

    int main(int argc, char* argv[])
    {
        myarray[0] = 3;
        return 0;
    }

make test:

    make
    gcc image1.c  -o image1
    gcc image2.c  -o image2
    ls -l image1 image2
    -rwxr-xr-x 1 gxp staff 106688 May 19 09:25 image1
    -rwxr-xr-x 1 gxp staff   4288 May 19 09:25 image2

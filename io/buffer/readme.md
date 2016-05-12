stdout & stderr
====

    //标准输出是行缓冲的，在缓冲区被填满或遇到换行符号前不会输出。
    fprintf(stdout, "a");
    //标准错误是不缓冲的，所以语句执行完后立刻显示出来。
    fprintf(stderr, "a has been written. ");
    fprintf(stdout, "b");
    fprintf(stderr, "b has been writeen. ");
    fprintf(stdout, "\n");

输出结果:

    a has been written. b has been writeen. ab

* 对于stdout，`\n`意味着换行与清空缓冲区；
* 对于stderr，`\n`只意味换行；

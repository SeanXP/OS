/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < times.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/22 >
  > Description:

     struct tms {
         clock_t tms_utime;  // user time
         clock_t tms_stime;  // system time
         clock_t tms_cutime; // user time of children
         clock_t tms_cstime; // system time of children
     };
 ****************************************************************/

#include <stdio.h>
#include <sys/times.h>

int main(int argc, char* argv[])
{
    struct tms tmsval;

    times(&tmsval);

    printf("user CPU time: %ld\n", tmsval.tms_utime);
    printf("system CPU time: %ld\n", tmsval.tms_stime);
    printf("user CPU time of all (waited for) children: %ld\n", tmsval.tms_cutime);
    printf("system CPU time of all (waited for) children: %ld\n", tmsval.tms_cstime);
    return 0;
}

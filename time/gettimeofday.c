/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < gettimeofday.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/22 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char* argv[])
{
    struct timeval tval;

    gettimeofday(&tval, NULL);
    printf("seconds: %ld\nmicroseconds: %d\n", tval.tv_sec, tval.tv_usec);

    time_t tt;
    tt = time(NULL);
    printf("seconds: %ld\n", tt);
    return 0;
}

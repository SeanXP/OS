/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < date.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/22 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{
    time_t tval;
    tval = time(NULL);
    printf("seconds: %ld\n", tval);

    //char *ctime(const time_t *timep);
    printf("ctime: %s", ctime(&tval));
    return 0;
}

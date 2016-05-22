/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < broken-down-time.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/22 >
  > Description:       transform date and time to broken-down time
 ****************************************************************/

#include <stdio.h>
#include <time.h>

void print_tm(struct tm *ptm)
{
    /*
    struct tm {
         int tm_sec;    // Seconds (0-60)
         int tm_min;    // Minutes (0-59)
         int tm_hour;   // Hours (0-23)
         int tm_mday;   // Day of the month (1-31)
         int tm_mon;    // Month (0-11)
         int tm_year;   // Year - 1900
         int tm_wday;   // Day of the week (0-6, Sunday = 0)
         int tm_yday;   // Day in the year (0-365, 1 Jan = 0)
         int tm_isdst;  // Daylight saving time
    };
    */
    printf("struct tm:\n");
    printf("\t tm_sec: %d\n",   ptm->tm_sec);
    printf("\t tm_min: %d\n",   ptm->tm_min);
    printf("\t tm_hour: %d\n",  ptm->tm_hour);
    printf("\t tm_mday: %d\n",  ptm->tm_mday);
    printf("\t tm_mon: %d\n",   ptm->tm_mon);
    printf("\t tm_year: %d\n",  ptm->tm_year);
    printf("\t tm_wday: %d\n",  ptm->tm_wday);
    printf("\t tm_yday: %d\n",  ptm->tm_yday);
    printf("\t tm_isdst: %d\n", ptm->tm_isdst);
}

int main(int argc, char* argv[])
{

    time_t tval;
    tval = time(NULL);
    printf("seconds: %ld\n", tval);

    struct tm * ptm;

    // gmtime()将日历时间转换为对应于UTC的分解时间；
    ptm = gmtime(&tval);
    print_tm(ptm);

    // localtime()将日历时间转换为对应于系统本地时间的分解时间；
    ptm = localtime(&tval);
    print_tm(ptm);
    return 0;
}

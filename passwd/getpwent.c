/****************************************************************
  Copyright (C) 2016 Sean Guo. All rights reserved.

  > File Name:         < getpwent.c >
  > Author:            < Sean Guo >
  > Mail:              < iseanxp+code@gmail.com >
  > Created Time:      < 2016/05/20 >
  > Description:
 ****************************************************************/

#include <stdio.h>
#include <pwd.h>

int main(int argc, char* argv[])
{

    struct passwd *pwd;

    while((pwd = getpwent()) != NULL)
        printf("%-8s %5ld\n", pwd->pw_name, (long)pwd->pw_uid);
    endpwent();
    return 0;
}

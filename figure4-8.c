/*
 * 程序清单 4-8 chdir 函数实例
 */

#include "apue.h"

int
main(void)
{
  if (chdir("/tmp") < 0)
    err_sys("chdir failed");
  printf("chdir to /tmp succeeded\n");
  exit(0);
}

/* figure4-8.c */

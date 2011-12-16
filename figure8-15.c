/*
 * 程序清单 8-15 打印实际和有效用户 ID
 */

#include "apue.h"

int
main(void)
{
  printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
  exit(0);
}

/* figure8-15.c ends here */

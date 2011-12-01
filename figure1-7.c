/*
 * 程序清单 1-7 打印用户 ID 和组 ID
 */

#include "apue.h"

int
main(void)
{
  printf("uid = %d, gid = %d\n", getuid(), getgid());
  exit(0);
}

/* figure1-7.c ends here */

/* 程序清单 4-3 umask 函数实例 */

#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int
main(void)
{
  umask(0);
  if (creat("foo", RWRWRW) < 0)
    err_sys("creat error for foo");
  umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if (creat("bar", RWRWRW) < 0)
    err_sys("creat error for bar");
  exit(0);
}

/* figure4-3.c ends here */

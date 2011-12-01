/*
 * 程序清单 1-6 例示 stderror 和 perror
 *
 * 对于 errno 应当知道两条规则：
 *     1. 如果没有出错，则其值不会被一个例程清除
 *     2. 任一函数都不会将 errno 值设置为 0，在 <errno.h> 中定义的所有常量都不为 0
 */

#include "apue.h"
#include <errno.h>

int
main(int argc, char *argv[])
{
  fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
  errno = ENOENT;
  perror(argv[0]);
  exit(0);
}

/* figure1-6.c ends here */

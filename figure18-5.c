/*
 * 程序清单 18-5 测试 isatty 函数
 */

#include "apue.h"

int
main(void)
{
  printf("fd 0: %s\n", isatty(0) ? "tty" : "not a tty");
  printf("fd 1: %s\n", isatty(1) ? "tty" : "not a tty");
  printf("fd 2: %s\n", isatty(2) ? "tty" : "not a tty");

  exit(0);
}

/* figure18-5.c ends here */

/*
 * 程序清单 5-1 用 getc 和 putc 将标准输入复制到标准输出
 */

#include "apue.h"

int
main(void)
{
  int c;

  while ((c = getc(stdin)) != EOF)
    if (putc(c, stdout) == EOF)
      err_sys("output error");

  if (ferror(stdin))
    err_sys("input error");

  exit(0);
}

/* figure5-1.c ends here */

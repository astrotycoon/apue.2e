/*
 * 程序清单 5-2 用 fgets 和 fputs 将标准输入复制到标准输出
 */

#include "apue.h"

int
main(void)
{
  char buf[MAXLINE];

  while (fgets(buf, sizeof(buf)/sizeof(buf[0]), stdin) != NULL)
    if (fputs(buf, stdout) == EOF)
      err_sys("output error");

  if (ferror(stdin))
    err_sys("input error");

  exit(0);
}

/* figure5-2.c */

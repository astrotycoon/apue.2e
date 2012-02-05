/*
 * 程序清单 15-6 将大写字符转换成小写字符的过滤程序
 */

#include "apue.h"
#include <ctype.h>

int
main(void)
{
  int c;

  while ((c = getchar()) != EOF) {
    if (isupper(c))
      c = tolower(c);
    if (putchar(c) == EOF)
      err_sys("output error");
    if (c == '\n')
      fflush(stdout);
  }
  exit(0);
}

/* figure15-6.c ends here */

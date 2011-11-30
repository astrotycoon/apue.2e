/*
 * 程序清单 18-9 调用 getpass 函数
 */

#include "apue.h"

char *getpass(const char *);

int
main(void)
{
  char *ptr;

  if ((ptr = getpass("Enter password:")) == NULL)
    err_sys("getpass error");
  printf("password: %s\n", ptr);

  /* now use password (probally encrypt it) ... */

  while (*ptr != 0)
    *ptr++ = 0;                 /* zero it out when we're done with it */

  exit(0);
}

/* figure18-9.c ends here */

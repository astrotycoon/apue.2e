/*
 * 程序清单 8-9 回送所有命令行参数和所有环境字符串
 */

#include "apue.h"

int
main(int argc, char *argv[])
{
  int           i;
  char          **ptr;
  extern char   **environ;

  for (i = 0; i < argc; i++)    /* echo all command-line args */
    printf("argv[%d]: %s\n", i, argv[i]);

  for (ptr = environ; *ptr != 0; ptr++) /* and all env strings */
    printf("%s\n", *ptr);

  exit(0);
}

/* figure8-9.c ends here */

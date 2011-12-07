/*
 * 程序清单 7-3 将所有命令行参数回送到标准输出
 */

#include "apue.h"

int
main(int argc, char *argv[])
{
  int i;

  for (i = 0; i < argc; i++)    /* echo all command-line args */
    printf("argv[%d]: %s\n", i, argv[i]);
  exit(0);
}

/* figure7-3.c ends here */

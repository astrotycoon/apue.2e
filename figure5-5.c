/*
 * 程序清单 5-5 演示 tempnam 函数
 */

#include "apue.h"

int
main(int argc, char *argv[])
{
  if (argc != 3)
    err_quit("usage: a.out <directory> <prefix>");

  printf("%s\n", tempnam(argv[1][0] != ' ' ? argv[1] : NULL,
                         argv[2][0] != ' ' ? argv[2] : NULL));

  exit(0);
}

/* figure5-5.c ends here */

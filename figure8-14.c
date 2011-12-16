/*
 * 程序清单 8-14 用 system 执行命令行参数
 */

#include "apue.h"

int
main(int argc, char *argv[])
{
  int status;

  if (argc < 2)
    err_quit("command-line argument required");

  if ((status = system(argv[1])) < 0)
    err_sys("system() error");
  pr_exit(status);

  exit(0);
}

/* figure8-14.c ends here */

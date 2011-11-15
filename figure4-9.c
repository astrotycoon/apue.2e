/*
 * 程序清单 4-9 getcwd 函数实例
 */

#include "apue.h"

int
main(void)
{
  char *ptr;
  int size;

  if (chdir("/usr/lib/gcc/i686-linux-gnu/4.4.5/include") < 0)
    err_sys("chdir failed");

  ptr = path_alloc(&size);      /* our own function */
  if (getcwd(ptr, size) == NULL)
    err_sys("getcwd failed");

  printf("cwd = %s\n", ptr);
  exit(0);
}

/* figure4-9.c */

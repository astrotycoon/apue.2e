/* 程序清单 4-5 打开一个文件，然后 unlink 它 */

#include "apue.h"
#include <fcntl.h>

int
main(void)
{
  if (open("tempfile", O_RDWR) < 0)
    err_sys("open error");
  if (unlink("tempfile") < 0)
    err_sys("unlink error");
  printf("file unlinked\n");
  sleep(15);
  printf("done\n");
  exit(0);
}

/* figure4-5.c */

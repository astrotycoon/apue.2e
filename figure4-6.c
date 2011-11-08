/*
 * 程序清单 4-6 中的程序使用带 O_TRUNC 选项的 open 函数将文件长度截短为 0，但并不是
 * 更改其访问时间及修改时间。为了做到这一点，首先用 stat 函数得到这些时间，然后截短文件，
 * 最后再用 utime 函数复位这两个时间。
 */

#include "apue.h"
#include <fcntl.h>
#include <utime.h>

int
main(int argc, char *argv[])
{
  int i, fd;
  struct stat statbuf;
  struct utimbuf timebuf;

  for (i = 1; i < argc; i++) {
    if (stat(argv[i], &statbuf) < 0) { /* fetch current times */
      err_ret("%s: stat error", argv[i]);
      continue;
    }
    if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { /* truncate */
      err_ret("%s: open error", argv[i]);
      continue;
    }
    close(fd);
    timebuf.actime  = statbuf.st_atime;
    timebuf.modtime = statbuf.st_mtime;
    if (utime(argv[i], &timebuf) < 0) { /* reset time */
      err_ret("%s: utime error", argv[i]);
      continue;
    }
  }
  exit(0);
}

/* figure4-6 ends here */

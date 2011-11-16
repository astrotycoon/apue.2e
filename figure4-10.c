/*
 * 程序清单 4-10 打印 st_dev 和 st_rdev 值
 *
 * 为每个命令行参数打印设备号，另外，若此参数引用的是字符特殊文件或块特殊文件，
 * 则还会打印该特殊文件的 st_rdev 值。
 */

#include "apue.h"
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif
#include <sys/sysmacros.h>      /* Linux, for `major' `minor' macro */

int
main(int argc, char *argv[])
{
  int i;
  struct stat buf;

  for (i = 1; i < argc; i++) {
    printf("%s: ", argv[i]);
    if (stat(argv[i], &buf) < 0) {
      err_ret("stat error");
      continue;
    }

    printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
    if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
      printf(" (%s) rdev = %d/%d",
             (S_ISCHR(buf.st_mode)) ? "character" : "block",
             major(buf.st_rdev), minor(buf.st_rdev));
    }
    printf("\n");
  }

  exit(0);
}

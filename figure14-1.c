/*
 * 程序清单 14-1 长的非阻塞 write
 *
 * 这时一个非阻塞 I/O 的实例，它从标准输入读 500,000 字节，并试图将它们写到标准
 * 输出上。该程序先将标准输出设置为非阻塞的，然后用 for 循环进行输出，每次 write
 * 调用的结果都在标准出错上打印。
 *
 * 函数 clr_fl() 类似与程序清单 3-5 中的 set_fl()，但与 set_fl() 的功能相反，
 * 它清楚 1 个或多个标志位。
 */

#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char buf[500000];

int
main(void)
{
  int   ntowrite, nwrite;
  char  *ptr;

  ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
  fprintf(stderr, "read %d bytes\n", ntowrite);

  set_fl(STDOUT_FILENO, O_NONBLOCK); /* set nonblocking */

  ptr = buf;
  while (ntowrite > 0) {
    errno = 0;
    nwrite = write(STDOUT_FILENO, ptr, ntowrite);
    fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

    if (nwrite > 0) {
      ptr += nwrite;
      ntowrite -= nwrite;
    }
  }
  clr_fl(STDOUT_FILENO, O_NONBLOCK); /* clear nonblocking */

  exit(0);
}

/* figure14-1.c ends here */

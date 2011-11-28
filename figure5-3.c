/*
 * 程序清单 5-3 对各个标准 I/O 流打印缓冲状态信息
 */

#include "apue.h"

void pr_stdio(const char *, FILE *);

int
main(void)
{
  FILE          *fp;

  fputs("enter any character\n", stdout);
  if (getchar() == EOF)
    err_sys("getchar error");
  fputs("one line to standard error\n", stderr);

  pr_stdio("stdin", stdin);
  pr_stdio("stdout", stdout);
  pr_stdio("stderr", stderr);

  if ((fp = fopen("/etc/motd", "r")) == NULL)
    err_sys("fopen error");
  if (getc(fp) == EOF)
    err_sys("getc error");
  pr_stdio("/etc/motd", fp);

  exit(0);
}

void
pr_stdio(const char *name, FILE *fp)
{
  printf("stream = %s, ", name);

  /*
   * The following is nonportable.
   */
  if (fp->_IO_file_flags & _IO_UNBUFFERED)
    printf("unbuffered");
  else if (fp->_IO_file_flags & _IO_LINE_BUF)
    printf("line buffered");
  else /* if neither of above */
    printf("fully buffered");
  printf(", buffer size = %d\n", fp->_IO_buf_end - fp->_IO_buf_base);
}

/* figure5-3.c ends here */

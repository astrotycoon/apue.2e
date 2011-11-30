/*
 * 程序清单 18-4 POSIX.1 isatty 函数的实现
 */

#include <termios.h>

int
isatty(int fd)
{
  struct termios ts;
  return (tcgetattr(fd, &ts) != -1); /* true if no error (is a tty) */
}

/* figure18-4.c ends here */

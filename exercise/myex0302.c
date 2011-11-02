/* 3.2 编写一个与 3.12 节中 dup2 功能相同的函数，要求不调用 fcntl 函数，并且要有正 */
/* 确的出错处理。 */

/* int dup2(int filedes, int filedes2); */

/* dup2 用 filedes2 参数指定新描述符的数值。如果 filedes2 已经打开，则先将其关闭。
   如若 filedes 等于 filedes2，则 dup2 返回 filedes2，而不关闭它。 */

/* 函数返回的新文件描述符与参数 filedes 共享同一个文件表项。 */

#include <stdio.h>              /* fprintf() */
#include <stdlib.h>             /* exit() */
#include <unistd.h>             /* dup() write() */

/* modup2: 功能与 dup2() 相同 */
int modup2(int filedes, int filedes2)
{
  int fd;
  if (filedes == filedes2)
    return filedes2;
  while ((fd = dup(filedes)) != filedes2)
    ;
  return filedes2;
}

/* test driver */
int main(void)
{
  int fd;
  char buf[] = "just do it.\n";

  fd = modup2(STDOUT_FILENO, 5);
  if (write(fd, buf, sizeof(buf)) != sizeof(buf))
    fprintf(stderr, "write error.\n");
  exit(0);
}

/* myex0302.c ends here */

/* 3.2 编写一个与 3.12 节中 dup2 功能相同的函数，要求不调用 fcntl 函数，并且要有正 */
/* 确的出错处理。 */

/* int dup2(int filedes, int filedes2); */

/* dup2 用 filedes2 参数指定新描述符的数值。如果 filedes2 已经打开，则先将其关闭。
   如若 filedes 等于 filedes2，则 dup2 返回 filedes2，而不关闭它。 */

/* 函数返回的新文件描述符与参数 filedes 共享同一个文件表项，若出错则返回 -1。 */

#include <stdio.h>              /* fprintf() */
#include <stdlib.h>             /* exit() perror() */
#include <string.h>             /* strlen() */
#include <unistd.h>             /* dup() write() */
#include <errno.h>              /* errno */

/* modup2: 功能与 dup2() 相同 */
int modup2(int filedes, int filedes2)
{
  int fd, tmpfd, fds[filedes2];
  int errsv = 0;

  if (filedes < 0
#ifdef OPEN_MAX
      || filedes >= OPEN_MAX
#endif
      ) {
    fprintf(stderr, "filedes: invalid file descriptor %d\n", filedes);
    return -1;
  }

  if (filedes2 < 0
#ifdef OPEN_MAX
      || filedes2 >= OPEN_MAX
#endif
      ) {
    fprintf(stderr, "filedes2: invalid file descriptor %d\n", filedes2);
    return -1;
  }

  if (filedes == filedes2)
    return filedes2;

  if ((tmpfd = dup(filedes2)) != -1) {
    if (close(filedes2) == -1)
      perror("close");
    if (close(tmpfd) == -1)
      perror("close");
  }

  int i = 0;
  while ((fd = dup(filedes)) != filedes2) {
    if (fd == -1) {
      errsv = fd;
      break;
    }
    fds[i++] = fd;
  }

  int j;
  for (j = 0; j < i ; ++j)
    if (close(fds[j]) == -1)
      perror("close");

  if (errsv != 0) {
    errno = errsv;
    return -1;
  }

  return filedes2;
}

/* test driver */
int main(void)
{
  int fd, n;
  char buf[] = "just do it.\n";

  n = strlen(buf);

  printf("\tmodup2(STDOUT_FILENO, 5):\n");
  fd = modup2(STDOUT_FILENO, 5);
  if (write(fd, buf, n) != n)
    perror("write");

  printf("\tmodup2(-1, 6):\n");
  fd = modup2(-1, 6);
  if (write(fd, buf, n) != n)
    perror("write");

  printf("\tmodup2(1, -1):\n");
  fd = modup2(1, -1);
  if (write(fd, buf, n) != n)
    perror("write");

  exit(0);
}

/* myex0302.c ends here */

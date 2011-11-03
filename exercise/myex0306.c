#include <stdio.h>              /* printf() */
#include <stdlib.h>             /* exit() */

#include <fcntl.h>              /* open() */
#include <unistd.h>             /* lseek() read() write() */

#define BUFFSIZE 4096
#define RSIZE 5

int main(void)
{
  int fd, n;
  char buf[BUFFSIZE];

  fd = open("/tmp/hello", O_RDWR | O_APPEND);

  if (lseek(fd, 0, SEEK_SET) == -1)
    printf("cannot seek\n");
  else
    printf("seek OK\n");

  if ((n = read(fd, buf, RSIZE)) != -1)
    printf("read OK\n");

  if (write(fd, buf, RSIZE) == RSIZE)
    printf("write OK\n");

  lseek(fd, 5, SEEK_SET);
  if (write(fd, buf, RSIZE) == RSIZE)
    printf("write OK, again\n");

  exit(0);
}

/* myex0306.c ends here */

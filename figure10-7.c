/*
 * 程序清单 10-7 具有超时限制的 read 调用
 */

#include "apue.h"

static void sig_alrm(int);

int
main(void)
{
  int n;
  char line[MAXLINE];

  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    err_sys("signal (SIGALRM) error");

  alarm(10);
  if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
    err_sys("read error");
  alarm(0);

  write(STDOUT_FILENO, line, n);
  exit(0);
}

static void
sig_alrm(int signo)
{
  /* nothing to do, just return to interrupt the read */
}

/* figure10-7.c ends here */

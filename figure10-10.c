/*
 * 程序清单 10-10 为进程打印信号屏蔽字
 *
 * #include <signal.h>
 * int sigprocmask(int how, const sigset_t *restrict set,
 *                 sigset_t *restrict oset);
 *
 * 返回值：若成功返回 0，若出错返回 -1
 */

#include "apue.h"
#include <errno.h>

void
pr_mask(const char *str)
{
  sigset_t sigset;
  int errno_save;

  errno_save = errno;           /* we can be called by signal handlers */
  if (sigprocmask(0, NULL, &sigset) < 0)
    err_sys("sigprocmask error");

  printf("%s", str);
  if (sigismember(&sigset, SIGINT))     printf("SIGINT ");
  if (sigismember(&sigset, SIGQUIT))    printf("SIGQUIT ");
  if (sigismember(&sigset, SIGUSR1))    printf("SIGUSR1 ");
  if (sigismember(&sigset, SIGALRM))    printf("SIGALRM ");

  /* remaining signals can go here */

  printf("\n");
  errno = errno_save;
}

/* figure10-10.c ends here */

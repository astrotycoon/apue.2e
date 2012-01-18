/*
 * 程序清单 10-12 用 sigaction 实现的 signal 函数
 */

#include "apue.h"

/* Reliable version of signal(), using POSIX sigaction(). */
Sigfunc *
signal(int signo, Sigfunc *func)
{
  struct sigaction act, oact;

  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
  } else {
#ifdef SA_RESTART
    act.sa_flags |= SA_RESTART;
#endif
  }
  if (sigaction(signo, &act, &oact) < 0)
    return SIG_ERR;
  return oact.sa_handler;
}

/* figure10-12.c ends here */

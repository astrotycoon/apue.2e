/*
 * 程序清单 10-4 sleep 的简单而不完整的实现
 */

#include <signal.h>
#include <unistd.h>

static void
sig_alrm(int signo)
{
  /* nothing to do, just return to wake up the pause */
}

unsigned int
sleep1(unsigned int nsecs)
{
  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    return nsecs;
  alarm(nsecs);                 /* start the timer */
  pause();                      /* next caught signal wakes us up */
  return alarm(0);              /* turn off timer, return unslept time */
}

/* figure10-4.c ends here */

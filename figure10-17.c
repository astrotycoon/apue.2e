/*
 * 程序清单 10-17 父子进程可用来实现同步的例程
 *
 * 可以用信号实现父、子进程之间的同步，这是信号应用的另一个实例。此程序清单
 * 包含了 8.9 节提到的五个例程的实现，它们是：TELL_WAIT、TELL_PARENT、
 * TELL_CHILD、WAIT_PARENT、WAIT_CHILD。
 */

#include "apue.h"

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo)              /* one signal handler for SIGUSR1 and SIGUSR2 */
{
  sigflag = 1;
}

void
TELL_WAIT(void)
{
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    err_sys("signal (SIGUSR1) error");
  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    err_sys("signal (SIGUSR2) error");
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGUSR1);
  sigaddset(&newmask, SIGUSR2);

  /*
   * Block SIGUSR1 and SIGUSR2, and save current signal mask.
   */
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    err_sys("SIG_BLOCK error");
}

void
TELL_PARENT(pid_t pid)
{
  kill(pid, SIGUSR2);           /* tell parent we're done */
}

void
WAIT_PARENT(void)
{
  while (sigflag == 0)
    sigsuspend(&zeromask);      /* and wait for parent */
  sigflag = 0;

  /*
   * Reset signal mask to original value.
   */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
}

void
TELL_CHILD(pid_t pid)
{
  kill(pid, SIGUSR1);           /* tell child we're done */
}

void
WAIT_CHILD(void)
{
  while (sigflag == 0)
    sigsuspend(&zeromask);      /* and wait for child */
  sigflag = 0;

  /*
   * Reset signal mask to original value.
   */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
}

/* figure10-17.c ends here */

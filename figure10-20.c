/*
 * 程序清单 10-20 system 函数的 POSIX.1 正确实现
 *
 * POSIX.1 要求 system 忽略 SIGINT 和 SIGQUIT，阻塞 SIGCHLD。
 *
 * POSIX.1 指出，在 SIGCHLD 未决期间，如若 wait 或 waitpid 返回了子进程的状态，
 * 那么 SIGCHLD 信号不应递送给该父进程，除非另一个子进程的状态可用。apue.2e 这本书
 * 讨论的四种实现都没有实现这种语义。作为替代，在 system() 调用了 waitpid()
 * 后，SIGCHLD 保持为未决；当解除了对此信号的阻塞后，它被递送至调用者。如果我们
 * 在 figure10-19.c 的 sig_chld() 中调用 wait()，则它将返回 -1，
 * 并将 errno 设置为 ECHILD，因为 system() 已取得子进程的终止状态。
 */

#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

int
system(const char *cmdstring)   /* with appropriate signal handling */
{
  pid_t pid;
  int status;
  struct sigaction ignore, saveintr, savequit;
  sigset_t chldmask, savemask;

  if (cmdstring == NULL)
    return 1;                   /* always a command processor with UNIX */

  ignore.sa_handler = SIG_IGN;  /* ignore SIGINT and SIGQUIT */
  sigemptyset(&ignore.sa_mask);
  ignore.sa_flags = 0;
  if (sigaction(SIGINT, &ignore, &saveintr) < 0)
    return -1;
  if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
    return -1;
  sigemptyset(&chldmask);       /* now block SIGCHLD */
  sigaddset(&chldmask, SIGCHLD);
  if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
    return -1;

  if ((pid = fork()) < 0) {
    status = -1;                /* probably out of processes */
  } else if (pid == 0) {        /* child */
    /* restore previous signal actions & reset signal mask */
    sigaction(SIGINT, &saveintr, NULL);
    sigaction(SIGQUIT, &savequit, NULL);
    sigprocmask(SIG_SETMASK, &savemask, NULL);

    execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
    _exit(127);                 /* exec error */
  } else {                      /* parent */
    while (waitpid(pid, &status, 0) < 0)
      if (errno != EINTR) {
        status = -1;            /* error other than EINTR from waitpid() */
        break;
      }
  }

  /* restore previous signal actions & reset signal mask */
  if (sigaction(SIGINT, &saveintr, NULL) < 0)
    return -1;
  if (sigaction(SIGQUIT, &savequit, NULL) < 0)
    return -1;
  if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
    return -1;

  return status;
}

/* figure10-20.c ends here */

/*
 * 程序清单 10-22 如何处理 SIGTSTP
 *
 * $ gcc err.c figure10-12.c figure10-22.c
 *
 * 此程序例示了当一个程序处理作业控制时所使用的规范代码序列。该程序只是将其标准
 * 输入复制到其标准输出，而在信号处理程序中以注释形式给出了管理屏幕的程序所执行
 * 的典型操作。
 *
 * 当程序启动时，仅当 SIGTSTP 信号的配置是 SIG_DFL，它才安排捕捉该信号。
 * 其理由是：当此程序由不支持作业控制的 shell （例如 /bin/sh） 启动时，
 * 此信号的配置应当设置为 SIG_IGN。实际上，shell 并不显式地忽略此信号，
 * 而是由 init 将这三个作业控制信号 SIGTSTP、SIGTTIN、SIGTTOU 设置
 * 为 SIG_IGN。然后，这种配置由所有登录 shell 继承。
 *
 * 只有作业控制 shell 才应该将这三个信号复位为 SIG_DFL。
 *
 * POSIX.1 认为有 6 个与作业控制有关：
 *     SIGCHLD 子进程已停止或终止
 *     SIGCONT 如果进程已停止，则使其继续运行
 *     SIGSTOP 停止信号（不能被捕捉或忽略）
 *     SIGTSTP 交互式停止信号
 *     SIGTTIN 后台进程组成员读控制终端
 *     SIGTTOU 后台进程组成员写到控制终端
 *
 * 除了 SIGCHLD 以外，大多数应用程序并不处理这些信号：交互式 shell 则通常
 * 处理这些信号的所有工作。
 */

#include "apue.h"

#define BUFFSIZE 1024

static void sig_tstp(int);

int
main(void)
{
  int n;
  char buf[BUFFSIZE];

  /*
   * Only catch SIGTSTP if we're running with a job-control shell.
   */
  if (signal(SIGTSTP, SIG_IGN) == SIG_DFL)
    signal(SIGTSTP, sig_tstp);

  while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  exit(0);
}

static void
sig_tstp(int signo)             /* signal handler for SIGTSTP */
{
  sigset_t mask;

  /* ... move cursor to lower left corner,  reset tty mode ... */

  /*
   * Unblock SIGTSTP, since it's blocked while we're handling it.
   */
  sigemptyset(&mask);
  sigaddset(&mask, SIGTSTP);
  sigprocmask(SIG_UNBLOCK, &mask, NULL);

  signal(SIGTSTP, SIG_DFL);     /* reset disposition to default */

  kill(getpid(), SIGTSTP);      /* and send the signal to ourself */

  /* we won't return from the kill until we're continued */

  signal(SIGTSTP, sig_tstp);    /* reestablish signal handler */

  /* ... reset tty mode, redraw screen ... */
}

/* figure10-22.c ends here */

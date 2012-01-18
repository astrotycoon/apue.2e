/*
 * 程序清单 10-14 信号屏蔽字、sigsetjmp 和 siglongjmp 实例
 *
 * 这个程序演示了在信号处理程序被调用时，系统所设置的信号屏蔽字如何自动地包括刚
 * 被捕捉到的信号。该程序也通过实例说明了如何使用 sigsetjmp() 和 siglongjmp()
 *
 * 此程序演示了另一种技术，只要在信号处理程序中调用 siglongjmp()，就应使用这种技术。
 * 仅在调用 sigsetjmp() 之后才将变量 canjump 设置为非 0 值。在信号处理程序中
 * 检测此变量，仅当它为非 0 值才调用 siglongjmp()。
 *
 * 这提供了一种保护机制，使得在 jmpbuf（跳转缓冲）尚未由 sigsetjmp() 初始化时，
 * 防止调用信号处理程序。在一般的 C 代码中（不是信号处理程序），对于 longjmp()
 * 并不需要这种保护措施。但是，因为信号可能在任何时候发生，所以在信号处理程序中，
 * 需要这种保护措施。
 *
 * 在程序中使用了数据类型 sig_atomic_t，这是由 ISO C 标准定义的变量类型，在写
 * 这种变量类型的变量时不会被中断。它意味着在具有虚拟存储器的系统上这种变量不会
 * 跨越页边界，可以用一条机器指令对其进行访问。这种类型的变量总是包括 ISO 类型
 * 修饰符 volatile，其原因是：该变量将由两个不同的控制线程 -- main 函数和异步
 * 执行的信号处理程序访问。
 */

#include "apue.h"
#include <setjmp.h>
#include <time.h>

static void sig_usr1(int), sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int
main(void)
{
  if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
    err_sys("signal (SIGUSR1) error");

  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    err_sys("signal (SIGALRM) error");
  pr_mask("starting main: ");

  if (sigsetjmp(jmpbuf, 1)) {
    pr_mask("ending main: ");
    exit(0);
  }
  canjump = 1;                  /* now sigsetjmp() is OK */

  for ( ; ; )
    pause();
}

static void
sig_usr1(int signo)
{
  time_t starttime;

  if (canjump == 0)
    return;                     /* unexpected signal, ignore */

  pr_mask("starting sig_usr1: ");
  alarm(3);                     /* SIGALRM in 3 seconds */
  starttime = time(NULL);
  for ( ; ; )                   /* busy wait for 5 seconds */
    if (time(NULL) > starttime + 5)
      break;
  pr_mask("finishing sig_usr1: ");

  canjump = 0;
  siglongjmp(jmpbuf, 1);        /* jump back to main, don't return */
}

static void
sig_alrm(int signo)
{
  pr_mask("in sig_alrm: ");
}

/* figure10-14.c ends here */

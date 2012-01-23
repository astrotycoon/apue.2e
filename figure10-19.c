/*
 * 程序清单 10-19 用 system 调用 ed 编辑器
 *
 * $ gcc err.c figure8-12.c figure10-12.c figure10-19.c
 *
 * 此程序使用 8.13 节中的 system 版本，用其调用 ed(1) 编辑器。（ed 很久以来
 * 就是 UNIX 的组成部分。在这里使用它的原因是：它是捕捉中断和退出信号的交互程序。
 * 若从 shell 调用 ed，并键入中断字符，则它捕捉中断信号并打印问号。它还将对
 * 退出符的处理方式设置为忽略。）
 */

#include "apue.h"

static void
sig_int(int signo)
{
  printf("caught SIGINT\n");
}

static void
sig_chld(int signo)
{
  printf("caught SIGCHLD\n");
}

int
main(void)
{
  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal (SIGINT) error");
  if (signal(SIGCHLD, sig_chld) == SIG_ERR)
    err_sys("signal (SIGCHLD) error");
  if (system("/bin/ed") < 0)
    err_sys("system() error");
  exit(0);
}

/* figure10-19.c ends here */

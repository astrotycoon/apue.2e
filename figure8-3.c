/*
 * 程序清单 8-3 打印 exit 状态的说明
 */

#include "apue.h"
#include <sys/wait.h>

void
pr_exit(int status)
{
  if (WIFEXITED(status))
    printf("normal termination, exit status = %d\n",
           WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    printf("abnormal termination, signal number = %d%s\n",
           WTERMSIG(status),
#ifdef WCOREDUMP
           WCOREDUMP(status) ? " (core file generated)" : "");
#else
           "");
#endif
  else if (WIFSTOPPED(status))
    printf("child stopped, signal number = %d\n",
           WSTOPSIG(status));
}

/* figure8-3.c ends here */

/*
 * 程序清单 8-10 执行一个解释器文件的程序
 */

#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {        /* child */
    if (execl("/home/mofaph/bin/testinterp",
              "testinterp", "myarg1", "MY ARG2", (char *)0) < 0)
      err_sys("execl error");
  }
  if (waitpid(pid, NULL, 0) < 0) /* parent */
    err_sys("waitpid error");
  exit(0);
}

/* figure8-10.c ends here */

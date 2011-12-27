/*
 * 程序清单 10-2 在信号处理程序中调用不可重入函数
 */

#include "apue.h"
#include <pwd.h>

static void
my_alarm(int signo)
{
  struct passwd *rootptr;

  printf("in signal handler\n");
  if ((rootptr = getpwnam("root")) == NULL)
    err_sys("getpwnam(root) error");
  alarm(1);
}

int
main(void)
{
  struct passwd *ptr;

  signal(SIGALRM, my_alarm);
  alarm(1);
  for ( ; ; ) {
    if ((ptr = getpwnam("android")) == NULL)
      err_sys("getpwnam error");
    if (strcmp(ptr->pw_name, "android") != 0)
      printf("return value corrupted!, pw_name = %s\n",
             ptr->pw_name);
  }
}

/* figure10-2.c ends here */

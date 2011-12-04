/*
 * UNIX高级环境编程 习题 2.3
 *
 * 改写程序清单 2-4 的程序，使其在 sysconf 为 OPEN_MAX 限制返回 LONG_MAX 时，
 * 避免进行不必要的处理。
 *
 * 如果 OPEN_MAX 是未确定的或大得出奇（即等于 LONG_MAX），那么我们可以使用
 * getrlimit 以得到每个进程的最大打开文件描述符数。因为可以修改对每个进行的限制，
 * 所以我们不能将从前一个调用得到的值高速缓存起来（它可能已被更改）。
 */

#include "apue.h"
#include <limits.h>
#include <sys/resource.h>

/*
 * If OPEN_MAX is indeterminate, we're not
 * guaranteed that this is adequate.
 */
#define OPEN_MAX_GUESS 256

long
open_max(void)
{
  long openmax;
  struct rlimit rl;

  if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 ||
      openmax == LONG_MAX) {
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
      err_sys("can't get file limit");
    if (rl.rlim_max == RLIM_INFINITY)
      openmax = OPEN_MAX_GUESS;
    else
      openmax = rl.rlim_max;
  }

  return openmax;
}

/* myex0203.c ends here */

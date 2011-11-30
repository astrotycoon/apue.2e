/*
 * 程序清单 18-3 POSIX.1 ctermid 函数的实现
 */

#include <stdio.h>
#include <string.h>

static char ctermid_name[L_ctermid];

char *
ctermid(char *str)
{
  if (str == NULL)
    str = ctermid_name;
  return (strcpy(str, "/dev/tty")); /* strcpy() return str */
}

/* figure18-3.c ends here */

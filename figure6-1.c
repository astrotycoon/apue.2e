/*
 * 程序清单 6-1 getpwnam 函数
 */

#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *
getpwnam(const char *name)
{
  struct passwd *ptr;

  setpwent();
  while ((ptr = getpwent()) != NULL)
    if (strcmp(name, ptr->pw_name) == 0)
      break;                    /* found a match */
  endpwent();
  return ptr;                   /* ptr is NULL if no match found */
}

/* figure6-1.c ends here */

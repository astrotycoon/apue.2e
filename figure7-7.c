/*
 * 程序清单 7-7 自动变量的不正确使用
 */

#include <stdio.h>

#define DATAFILE "datafile"

FILE *
open_data(void)
{
  FILE *fp;
  char databuf[BUFSIZ];         /* setvbuf make this the stdio buffer */

  if ((fp = fopen(DATAFILE, "r")) == NULL)
    return NULL;
  if (setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
    return NULL;
  return fp;                    /* error */
}

/* figure7-7.c ends here */

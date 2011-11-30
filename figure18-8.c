/*
 * 程序清单 18-8 getpass 函数的实现
 *
 * getpass() 读入用户在终端上键入的口令。此函数由 UNIX login(1) 和 crypt(1)
 * 程序调用。为了读口令，该函数必须禁止回显，但仍可使终端以规范模式进行工作，
 * 因为用户在键入口令后，一定要键入回车，这样也就构成了一个完整行。
 *
 * 下面的实现是一个典型的 UNIX 实现。
 */

#include <signal.h>
#include <stdio.h>
#include <termios.h>

#define MAX_PASS_LEN 8          /* max #char for user to enter */

char *
getpass(const char *prompt)
{
  static char     buf[MAX_PASS_LEN + 1]; /* null byte at end */
  char           *ptr;
  sigset_t        sig, osig;
  struct termios  ts, ots;
  FILE           *fp;
  int             c;

  if ((fp = fopen(ctermid(NULL), "r+")) == NULL)
    return (NULL);
  setbuf(fp, NULL);

  sigemptyset(&sig);
  sigaddset(&sig, SIGINT);      /* block SIGINT */
  sigaddset(&sig, SIGTSTP);     /* block SIGTSTP */
  sigprocmask(SIG_BLOCK, &sig, &osig); /* and save mask */

  tcgetattr(fileno(fp), &ts);   /* save tty state */
  ots = ts;                     /* structure copy */
  ts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
  tcsetattr(fileno(fp), TCSAFLUSH, &ts);
  fputs(prompt, fp);

  ptr = buf;
  while ((c = getc(fp)) != EOF && c != '\n')
    if (ptr < &buf[MAX_PASS_LEN])
      *ptr++ = c;
  *ptr = 0;                     /* null terminate */
  putc('\n', fp);               /* we echo a newline */

  tcsetattr(fileno(fp), TCSAFLUSH, &ots); /* restore TTY state */
  sigprocmask(SIG_SETMASK, &osig, NULL);  /* restore mask */
  fclose(fp);                             /* done with /dev/tty */
  return (buf);
}

/* figure18-8.c ends here */

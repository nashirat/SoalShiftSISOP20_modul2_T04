#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main (int argc, char *argv[]) {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  int sec, min, hr;
  hr = min = sec = -5;
  time_t t = time(NULL);
  struct tm lt = *localtime(&t);

  if (argc != 5) {
    printf ("Argumen Tidak Sesuai \n");
    return 0;
  }

  if ((isalpha(argv[1][0])) || (isalpha(argv[2][0])) || (isalpha(argv[3][0])) ) {
    printf ("Waktu harus angka\n");
    return 0;
  }

  if (argv[1][0] != '*') sec = atoi(argv[1]);
  if (argv[2][0] != '*') min = atoi(argv[2]);
  if (argv[3][0] != '*') hr = atoi(argv[3]);

  if ((sec >= 60 || sec < 0 && sec != -5 ) || (min >= 60 || min < 0 && min != -5) || (hr >= 25 || hr < 0 && hr != -5)) {
    printf("Format Waktu Salah\n");
    return 0;
  }

  while (1) {
  t = time(NULL);
  lt = *localtime(&t);
  if ((lt.tm_sec == sec || sec == -5) && (lt.tm_min == min || min == -5) && (lt.tm_hour == hr || hr == -5)) {
    if (fork()==0)
      execl("/bin/bash", "bash", argv[4], NULL);}
      sleep(1);
  }
}

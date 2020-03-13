#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <wait.h>
#include <unistd.h>
#include <sys/stat.h>

int statmake(const char *ph) {
  struct stat pathDir;
  stat(ph, &pathDir);
  return S_ISDIR(pathDir.st_mode);
}

int main() {
  pid_t c1 = fork();
  int c2 = fork();
  int c3 = fork();
  int stat;

  if (c2 > 0 && c3 > 0) {
    while ((wait(&stat)) > 0);
    DIR *loc;
    struct dirent *directory;
    chdir("/home/nash/modul2/jpg");
    loc = opendir(".");

    if (loc) {

      while ((directory = readdir(loc)) != NULL) {
        if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0)
        continue;

        if(statmake(directory->d_name)) {

          if(fork() == 0) {

            char files[500];
            sprintf(files, "/home/nash/modul2/jpg/%s", directory->d_name);
            char* argv[] = {"mv", files, "/home/nash/modul2/indomie/", NULL};
            execv("/bin/mv", argv);
          }
          else {
            while ((wait(&stat)) > 0);

            if (fork() == 0) {
              if(fork() == 0) {
                char txt1[500];
                FILE *file;
                sprintf(txt1, "/home/nash/modul2/indomie/%s/coba1.txt",directory->d_name);
                file = fopen(txt1, "w");
                fclose(file);
              }
              else {
                while ((wait(&stat)) > 0);
                sleep(3);
                char txt2[500];
                FILE *file;
                sprintf(txt2, "/home/nash/modul2/indomie/%s/coba2.txt",directory->d_name);
                file = fopen(txt2, "w");
                fclose(file);
                exit(0);
              }
            }
            else {
              while ((wait(&stat)) > 0);
              exit(0);
            }
          }
        }
        else {
          while ((wait(&stat)) > 0);
          if(fork() == 0) {
            while ((wait(&stat)) > 0);
            char done[500];
            sprintf(done, "/home/nash/modul2/jpg/%s",directory->d_name);
            char* newargv[] = {"mv", done, "/home/nash/modul2/sedaap/", NULL};
            execv("/bin/mv", newargv);
          }
        }
      }
    }
  }
  else if (c2 == 0 && c3 > 0) {
    while ((wait(&stat)) > 0);
    if (c1 == 0) {
      char *cindomie[] = {"mkdir", "-p", "/home/nash/modul2/indomie", NULL};
      execv("/bin/mkdir", cindomie);
    }
    else {
      while ((wait(&stat)) > 0);
      sleep(05);
      char *csedaap[] = {"mkdir", "-p", "/home/nash/modul2/sedaap", NULL};
      execv("/bin/mkdir", csedaap);
    }
  }
  else if (c2 > 0 && c3 == 0) {
    char* unzip[] = {"unzip", "-oq", "/home/nash/modul2/jpg.zip", NULL};
    execv("/usr/bin/unzip", unzip);
  }
  return 0;
}

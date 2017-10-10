#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int globvar = 6;

int main(void) {
  int var = 88;
  pid_t pid;

  printf("before fork\n");
  if ((pid = fork()) < 0) {
    fprintf(stderr, "fork failed\n");
    exit(-1);
  } else if (pid == 0) {
    globvar++; //child
    var++;
  } else {
    sleep(2); // parent
  }
  printf("pid = %d, globvar = %d, var = %d\n",
           getpid(), globvar, var);
  exit(0);
}

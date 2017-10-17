#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int globvar = 6;

void *simple_thr(void *arg) {
      globvar++; 
      // var++; Notice this variable is not accessible
      printf("New thread : pid = %d, tid = 0x%lx, globvar = %d, "
              "var = %s\n", getpid(), (unsigned long)pthread_self(),
              globvar, "Not accessible");
      pthread_exit(NULL);
}

int main(void) {
  int rc;
  int var = 88;
  pthread_t thread;

  printf("before thread create\n");
  rc = pthread_create(&thread, NULL, simple_thr, NULL);
  assert(rc == 0);
  pthread_join(thread, NULL);
  printf("Main thread: pid = %d, tid = 0x%lx, globvar = %d, " 
         "var = %d\n", getpid(), (unsigned long)pthread_self(), globvar, var);
  exit(0);
}


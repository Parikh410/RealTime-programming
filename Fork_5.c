/* This program prints a sequence of numbers from the
   parent and child processes respectively. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAX 20

int main() {

  pid_t pid;
  int i;
 
  pid = fork();
  if (pid==-1) {
    printf("The fork() has failed.\n");
    exit(1);
  }

  //A new process has been created.
  if (pid==0) {
    for (i=1; i<=MAX; i++)
      printf("Child process: id=%d, value of i=%d\n", pid, i);
  }
  else {
    for (i=1; i<=MAX; i++)
      printf("Parent process: id=%d,value of i=%d\n", pid, i);
  }

  return 0;
}

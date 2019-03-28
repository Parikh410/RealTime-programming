/* Program to generate a chain of processes. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define DEPTH 4

int main() {

  int i;
  pid_t pid;

  //Chain of processes.
  for (i=1; i<DEPTH; ++i) {

    if ((pid = fork()) < 0){ 
      printf("The fork failed.\n");
      exit(1);
    }

    if (pid==0)
      break;
  }

  printf("Level=%d id=%d parent id=%d child id=%d\n",
	      i, getpid(), getppid(), pid);

  return 0;
}

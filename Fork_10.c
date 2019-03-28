/* Program to illustrate the creation of a tree of processes. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define DEPTH 3

int main() {

  pid_t pid; 
  int i;

  for (i=0; i<DEPTH; i++) {

    if ((pid = fork()) < 0){ 
      printf("The fork failed.\n");
      exit(1);
    }

    if (pid==0) {
      printf("Level=%d id=%d parent id=%d child id=%d\n",
	      i, getpid(), getppid(), pid);
    }

    else {
      printf("Level=%d id=%d parent id=%d child id=%d\n",
	      i, getpid(), getppid(), pid);
    }
  }
  
  return 0;
}

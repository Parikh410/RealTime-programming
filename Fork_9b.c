/* This program illustrates the difference between the process 
   and child address spaces. */

#include <sys/types.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

int main() {

  pid_t pid;
  int testvar = 10;
  int *testptr = malloc(sizeof(int));
  *testptr = 24;

  pid = fork();
  if (pid==-1) { 
    printf("The fork failed.\n");
    exit(1);
  }

  if (pid>0) { //parent process
    testvar = 13;
    *testptr = 67;

    printf("Parent process: id=%d testvar=%d, testptr=%p, testptr_value=%d\n",
	    getpid(), testvar, testptr, *testptr);
  }
  else { //child process
    printf("Child process: id=%d testvar=%d, testptr=%p, testptr_value=%d\n",
	    getpid(), testvar, testptr, *testptr);
  }

  return 0;
}

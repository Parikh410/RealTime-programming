/* This program illustrates the difference between the process 
   and child address spaces ... to be completed during
   practical sessions. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

  pid_t pid;
  int testvar = 10;
  int *testptr = malloc(sizeof(int));

  pid = fork();

  if (pid==-1) { 
    printf("The fork failed.\n");
    exit(1);
  }

  if (pid>0) {
    /* Modify the value of testvar and value pointed to by testptr.*/
    /* Print in which process you are. */
    /* Print values of the process id, testvar, testptr and value pointed 
	to by testptr */ 
  }
  else {
    /* Print in which process you are. */
    /* Print values of the process id, testvar, testptr and value pointed
	to by testptr */ 
  }

  return 0;
}

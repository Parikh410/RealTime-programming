/* This program illustrates how to distinguish
   between the parent and child processes. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {

  pid_t pid;
 
  pid = fork();

  if (pid==-1) {
    printf("The fork() has failed.\n");
    exit(1);
  }

  //A new process has been created.
  if (pid==0)
    printf("The id of the child process is %d.\n", pid);
  else
    printf("The id of the parent process is %d.\n", pid);
  
  return 0;
}

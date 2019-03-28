/* Program to illustrate the wait call. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  pid_t pid, child_pid;
  int *status = NULL;

  //Create a new process
  pid=fork();
  if (pid<0) {
    printf("Fork failed...\n"); 
    exit(1);
  }
 
  //inside the child
  if (pid==0){
    printf("I am the child.\n");
  } 
 
  else {
    //parent waits for child; 
    child_pid = wait(status);
    printf("I am the parent. My child's process id was: %d\n", child_pid);
  }

  return 0;
}

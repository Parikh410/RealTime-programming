/* A program to illustrate the wait function. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

  pid_t pid, child_pid;
  int status;

  printf("I am the parent process with id %d\n", getpid());

  //Create a new process  
  pid=fork();

  if (pid<0) {
    printf("Fork failed...\n"); 
    exit(1);
  }

  //parent process
  if (pid!=0) {
    printf("I am the parent process with id %d and parent id %d.\n",
                  getpid(),getppid());
    //Wait for the child to terminate
    child_pid=wait(&status);
    printf("A child with pid %d terminated with exit code %d.\n",
                  child_pid, status>>8);
  }

  //child process
  else {
    printf("I am the child process with id %d and parent id %d.\n",
                  getpid(), getppid());
    //Exit with a randomly chosen number.
    exit(88);  
  }

  printf("Process with id %d terminates.\n", pid); 

  return 0;
}

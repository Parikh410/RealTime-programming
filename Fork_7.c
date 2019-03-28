/* Program to illustrate the use of getpid(). */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid;

  printf("I am the original process with id=%d.\n", getpid());
  pid=fork(); 

  if (pid==-1) {
    printf("The fork() has failed.\n");
    exit(1);
  }
  
  if (pid==0) { //executed only by the child process
    printf("I am the child process with id=%d.\n", getpid());
  }
  else { //executed only by the parent process
    printf("I am the parent process with id=%d.\n", getpid());
    printf("My child's pid=%d.\n", pid);
  }
  
  //Both parent and child processes execute the following:
  printf("pid=%d terminates.\n", getpid());  

  return 0;
}

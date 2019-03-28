/* Program to illustrate the use of getpid() and gettpid(). */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid;

  printf("I am the original process with id=%d and parent id=%d.\n", getpid(),getppid());
  pid=fork(); 

  if (pid==-1) {
    printf("The fork() has failed.\n");
    exit(1);
  }

  if (pid==0) { //executed only by child process
    printf("I am the child process with id=%d and parent id=%d.\n", getpid(),getppid());
  }
  else { //executed only by parent process
    printf("I am the parent process with id=%d and parent id=%d.\n", getpid(),getppid());
    printf("My child's id=%d.\n", pid);
  }

  //The following is executed by both parent and child processes:
  printf("pid=%d terminates.\n", getpid()); 

  return 0;
}

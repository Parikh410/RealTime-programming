/* This program prints a sequence of numbers from the
   parent and child processes respectively, using
   write system call instead of printf library calls. */

#define _GNU_SOURCE //This is required because asprintf is a GNU extension, not in C or POSIX
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX 3

int main() {

  pid_t pid;
  int i;
  char *buffer_string;
 
  pid = fork();

  if (pid==-1) {
    printf("The fork() has failed.\n");
    exit(1);
  }

  //A new process has been created.
  if (pid==0) {
    for (i=1; i<=MAX; i++) {
      printf("From the child process with id %d, value of i=%d\n", pid, i);     
    }
  }
  else {
    for (i=1; i<=MAX; i++) {
      printf( "From the parent process with id %d, value of i=%d\n", pid, i);    
    }
  }

  return 0;
}

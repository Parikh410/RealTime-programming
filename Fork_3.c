/* This program illustrates the use of the fork() system call
   and checks if it is successful. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  
  pid_t pid;
 
  pid = fork(); //A new process has been created.

  if (pid==-1) {
    printf("The fork() has failed.\n");
    exit(1);
  }

  printf("The fork has succeeded!\n");

  return 0;
}

/* This program illustrates the values returned by
   the fork() system call. */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

  pid_t pid;
 
  pid = fork(); //A new process has been created.

  printf("The id of this process is %d.\n", pid);

  return 0;
}

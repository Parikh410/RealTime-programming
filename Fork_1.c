/* This program illustrate the use of the fork() system call. */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  
  fork();
  printf("The fork has succeeded!\n");

  return 0;
}

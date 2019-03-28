/* A program to illustrate the zombie process. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t pid;
  pid=fork();
  
  if (pid<0) {
    printf("Fork failed...\n"); 
    exit(1);
  }
  
  //Parent process
  if (pid!=0) {
    while (1) // never terminate, and never execute a wait()
      sleep(10000);
  }

  //Child process
  else {
    exit(0); //exit with a given positive number
  }

  return 0;
}

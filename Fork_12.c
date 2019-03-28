/* Program to ilustrate the exec function. */

#include <sys/types.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

  pid_t  pid;

  pid = fork(); //create a new process
	
  if (pid<0){ 
    printf("The fork failed.\n");
    exit(-1);
  }
  else if (pid==0) { //child process
    if(execlp("/bin/cd", "cd", "..", NULL)<0)
		printf("Process not successful..\n"); //it executes the command ls
  }
  else { //parent process 
    wait(NULL); //parent will wait for the child to complete
    printf ("Child completes.");
    exit(0);
  }

  return 0;
}

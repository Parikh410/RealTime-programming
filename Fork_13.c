/* Program to illustrate the exec function */
/* A child process is forked and it executes a program
   passed as an argument. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXINT 9999999 

int main(int argc,  char *argv[],  char *envp[]) {
  int i, j; 
  pid_t pid;
  //char *path = malloc(256 * sizeof(char)); 
char *path;
  char *arguments_array[argc-1];

  printf("argc = %d\n", argc);
  if(argc<2) {
    printf("Usage: %s executable {arguments}\n", argv[0]); 
    exit(1);
  }

  path = argv[1];
  printf("Path to new executable:  %s \n", path);

  //Store the arguments in arguments_array
  if (argc>=2) {
    for(i=1; i<=argc; i++) 
      arguments_array[i-1] = argv[i];

    printf("Arguments are: \n"); 
    for(i=0; i<(argc-1); i++)
      printf("%d...  %s\n", i, arguments_array[i]);
  }

  pid = fork(); 
  if(pid<0) {
    printf("Fork failed...\n"); 
    exit(1);
  }

  if(pid==0) {
    if((execve(path, arguments_array, envp))<0 ) {
      printf("Child: The exec failed...\n"); 
      exit(1);
    }
  }

  if(pid>0) {
    i = 0;
    for(j=0;j<MAXINT;j++)
      i=(i*j)%10;
    exit(0);
  }

  return 0;
}

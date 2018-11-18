#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


int main(){

  printf("Ok so basically I'm parent\n");
  
  int i;
  for(i = 0; i < 2; i++){ 
    int f = fork();
    
    int fd = open("/dev/random", O_RDONLY);
    if(fd < 0){
      printf("Uh oh: %s\n", strerror(errno));
    }
    
    unsigned int * num = malloc(4);
    int * status = malloc(4);
    
    wait(status);
    
    if(f < 0){
      printf("%s\n", strerror(errno));
    }else if(f){
      printf( "That %d child just finished waiting for %d seconds\n", f, WEXITSTATUS(* status));
    }else if( f == 0){
      printf("I'm a child, my pid is %d\n", getpid());
      read(fd, num, 4);
      int number = (* num % 16) + 5;
      printf("I've decided to wait for %d seconds\n", number);
      sleep(number);
      printf("OK I'm done now\n");
      exit(number);
    }
  }
  printf("We done\n");
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


int main(){
    int f = fork();
    int fd = open("/dev/random", O_RDONLY);
    sleep(5);
    if(fd < 0){
        printf("Uh oh: %s\n", strerror(errno));
    }

    unsigned int * num = calloc(1,4);

    if(f < 0){
        printf("%s\n", strerror(errno));
    }else if(f){
        printf("Parent, %d\n", getpid());

    }else{
        printf("I'm a child, my pid is %d\n", getpid());
        read(fd, num, 4);
        printf("%d\n", (* num % 16) + 5);
        //sleep((* num % 16) + 5);
        sleep(5);
    }

    return 0;
}

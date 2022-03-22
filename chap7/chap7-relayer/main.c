#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <errno.h>
#include "relayer.h"
#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define TTY3 "/dev/tty10"
#define TTY4 "/dev/tty9"

int main(){
    int fd1,fd2;
    fd1 = open(TTY1,O_RDWR);
    if (fd1< 0){
        perror("open():");
        exit(1);
    }
    write(fd1,"tty1\n",5);
    fd2 = open(TTY1,O_RDWR | O_NONBLOCK);
    if (fd2< 0){
        perror("open():");
        exit(1);
    }
    write(fd1,"tty2\n",5);
    int job1 = rel_addjob(fd1,fd2);
    if (job1 < 0){
        fprintf(stderr,"error is : %S\n",strerror(-job1));
        exit(1);
    }
    while (1)
    {
        pause ;
    }
    
    close(fd1);
    close(fd2);
    exit(0);
}
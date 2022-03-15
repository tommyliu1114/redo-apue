#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
int main(){
    fflush(NULL);
    puts("begin!");
    execl("/usr/bin/date","date","+%s",NULL);
    perror("execle()");
    exit(1);
    puts("end!");
    exit(0);
}
*/

int main(){
    puts("begin!");
    fflush(NULL);
    pid_t pid;
    pid = fork();
    if (pid < 0){
        perror("fork()");
        exit(1);
    }
    if (pid == 0){
        execl("/usr/bin/date","date","+%s",NULL);
        perror("execle()");
        exit(1);      
    }
    wait(0);
    puts("main end");
}
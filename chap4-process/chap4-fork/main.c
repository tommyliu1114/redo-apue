#include <stdio.h> 
#include <unistd.h>  
#include <stdlib.h> 

int main(){
    pid_t pid;
    printf("[%d]begin!\n",getpid());
    fflush(NULL);//必须刷新流
    pid = fork();
    if (pid < 0 ){
        perror("fork()");
        exit(-1);
    }
    if (pid ==0 ){
        printf("[%d]: child is working \n",getpid());
    }else{
        printf("[%d]: parnet is working \n",getpid());
    }
    printf("[%d]end!\n",getpid());
    sleep(60);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc,char **argv){
    if (argc < 3){
        fprintf(stderr,"usage...\n");
        exit(1);
    }
    pid_t pid;
    pid = fork();
    if (pid < 0){
        perror("fork()");
        exit(1);
    }
    if (pid == 0){
        int setres ;
        setres = setuid(atoi(argv[1]));//这句很重要，可以分别将编译出来的文件赋予root用户，root粘贴位来分别观察这个值
        printf("setres is : %d \n",setres);
        execvp(argv[2],argv+2);
        perror("execvp()");
        exit(1);
    }
    wait(NULL);
    exit(0);
}
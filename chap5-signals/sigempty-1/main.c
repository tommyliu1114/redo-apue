#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


static void int_handler(int sig)
{
    write(1,"!",1);
}

int main()
{
    int i ,j;
    sigset_t set;
    sigset_t oldset;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    signal(SIGINT,int_handler);
    for(i=0;i<10;i++){
        sigprocmask(SIG_BLOCK,&set,&oldset);
        for(j=0;j<5;j++){
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        sigprocmask(SIG_UNBLOCK,&set,NULL);
    }
    exit(0);
}
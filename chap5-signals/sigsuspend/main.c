#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

//信号驱动程序

static void int_handler(int sig)
{
    write(1,"!",1);
}

int main()
{
    int i ,j;
    sigset_t set;
    sigset_t oldset,saveset;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_UNBLOCK,&set,&saveset);
    sigprocmask(SIG_BLOCK,&set,&oldset);
    signal(SIGINT,int_handler);
    for(i=0;i<10;i++){
        //sigprocmask(SIG_BLOCK,&set,&oldset);
        for(j=0;j<5;j++){
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        sigsuspend(&oldset);
        // sigset_t tmpset;
       
        // sigprocmask(SIG_SETMASK,&oldset,&tmpset);
        //  pause();
        //  sigprocmask(SIG_SETMASK,&tmpset,NULL);
    }
    sigprocmask(SIG_SETMASK,&saveset,NULL);
    exit(0);
}
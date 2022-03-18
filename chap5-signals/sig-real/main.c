#include <signal.h> 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MYRTSIG SIGRTMIN+6

void int_handler(int s){
    write(1,"====",4);
}
int main(){
    //signal(SIGINT,SIG_IGN); //忽略信号
    signal(MYRTSIG,int_handler);
    for(int j = 0;j<10;j++){
            for (int i = 0;i< 5;i++){
        write(1,"*",1);
        sleep(1);
    }
    write(1,"\n",1);
    }
    exit(0);
}
//实时信号排队，且不丢失
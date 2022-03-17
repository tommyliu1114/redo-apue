#include <signal.h> 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
void int_handler(int s){
    write(1,"====",4);
}
int main(){
    //signal(SIGINT,SIG_IGN); //忽略信号
    signal(SIGINT,int_handler);
    for (int i = 0;i< 10;i++){
        write(1,"*",1);
        sleep(1);
    }
    exit(0);
}
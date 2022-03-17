#include <signal.h> 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

// int main(){
//     alarm(5);
//     pause();
//     exit(0);
// }

// int main(){
//     time_t end;
//     int64_t count = 0;
//     end = time(NULL) + 5;
//     while(time(NULL) <= end){
//         count++;
//     }
//     printf("%ld\n",count);
//     exit(0);
// }

static volatile int loop = 1; 
//注意olatile说明，一定要去内存中取，优化的时候异步程序如果不加olatile的话可能会被优化掉这个变量，认为i值不变化
static void alarm_handler(int s){
    loop = 0;
}

int main(){
    int64_t count = 0;
    alarm(5);
    signal(SIGALRM,alarm_handler);
    while(loop){
        count++;
    }
    printf("%ld",count);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define THRNUM 4 

#define LINESIZE 1024

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER ;

static pthread_cond_t conds = PTHREAD_COND_INITIALIZER;

static int num  = 0;

static int next(int n){
    return (n+1) % THRNUM;
}

static void* thr_func(void* p) {
    
    int n = (int)p;
    int c = 'a' +n;
    while (1)
    {
        pthread_mutex_lock(&mut);
        while(num != n)
            pthread_cond_wait(&conds,&mut);        
        write(1,&c,1);  
        num = next(num) ;     
        pthread_cond_broadcast(&conds); //通知下一个用户可以开始了
        pthread_mutex_unlock(&mut);
    }

    pthread_exit(NULL);

}



int main(){
    pthread_t tid[THRNUM];
    for (int i =0;i<THRNUM;i++){
        int err = pthread_create(tid+i,NULL,thr_func,(void *)i);
        if (err){
            fprintf(stderr,"pthread_create(): %s\n",strerror(err));
            exit(1);
        }
    }
    alarm(5);
    for (int i =0;i<THRNUM;i++){
        pthread_join(tid[i],NULL);
       
    }  
     pthread_mutex_destroy(&mut);
     pthread_cond_destroy(&conds);
    exit(0);
}


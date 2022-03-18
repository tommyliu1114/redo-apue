#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static void cleanup_func(void *p){
    puts(p);
}

static void *func (void* p ){
    puts("thread is working!");
    pthread_cleanup_push(cleanup_func,"cleanup:1");
    pthread_cleanup_push(cleanup_func,"cleanup:2");
    pthread_cleanup_push(cleanup_func,"cleanup:3");
    puts("push over!");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);
    //return NULL ;
    pthread_exit(NULL);//更专业，用return不能做线程堆栈的清理 
}

int main(){
    pthread_t tid;
    puts("begin!");
    int err ;
    err = pthread_create(&tid,NULL,func,NULL);
    if (err){
        fprintf(stderr,"pthread_create(): %s\n",strerror(err));
        exit(1);
    }
    pthread_join(tid,NULL);

    puts("ened!");
    exit(0);
}
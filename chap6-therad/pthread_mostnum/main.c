#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000300
#define THRNUM (RIGHT-LEFT+1)

struct thr_arg_st {
    int n;
    int resp ; //返回值
};

// static void cleanup_func(void *p){
//     puts(p);
// }

// static void *func (void* p ){
//     puts("thread is working!");
//     pthread_cleanup_push(cleanup_func,"cleanup:1");
//     pthread_cleanup_push(cleanup_func,"cleanup:2");
//     pthread_cleanup_push(cleanup_func,"cleanup:3");
//     puts("push over!");
//     pthread_cleanup_pop(1);
//     pthread_cleanup_pop(0);
//     pthread_cleanup_pop(1);
//     //return NULL ;
//     pthread_exit(NULL);//更专业，用return不能做线程堆栈的清理 
// }

static void* is_prime(void* num) {

    int pptr = 20;
    printf("%ld\n",&pptr);
    // 0 非素数，1 为素数 
    int inNum  = ((struct thr_arg_st * )num)->n;
    
    int retNum  = 0;
    if (inNum < 2) {
        ((struct thr_arg_st * )num)->resp = 1;
        pthread_exit(num );
    }
    for (int j =2;j< inNum/2;j++){
        if (inNum % j == 0){
            ((struct thr_arg_st * )num)->resp = 0;
             pthread_exit( num);
        }

    }
    ((struct thr_arg_st * )num)->resp = 1;
    //printf("%d is primer \n",inNum); 
    sleep(30);
    pthread_exit( num); 

}

int main(){
    // pthread_t tid;
    // puts("begin!");
    // int err ;
    // err = pthread_create(&tid,NULL,func,NULL);
    // if (err){
    //     fprintf(stderr,"pthread_create(): %s\n",strerror(err));
    //     exit(1);
    // }
    // pthread_join(tid,NULL);

    // puts("ened!");
    // exit(0);
    int i;
    pthread_t tid[RIGHT-LEFT+1];
    struct thr_arg_st *p;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr,100*1024*1024);
    for(i = LEFT;i<=RIGHT;i++){
       p = malloc(sizeof(*p));
        p->n = i;
        int err = pthread_create(&tid[i-LEFT],&attr,is_prime,p);
        if (err){
            fprintf(stderr,"phtread_create(): %s\n",strerror(err));
            exit(1);
        } 
    }
    for(i = LEFT;i<=RIGHT;i++){
        //pthread_join(tid[i-LEFT],NULL);
        struct thr_arg_st *ptemp;
        pthread_join(tid[i-LEFT],&ptemp);
        if (ptemp->resp == 1 ){
            fprintf(stdout,"in main , num %d is prime \n",i);
        }
        free(ptemp);
    }
    pthread_attr_destroy(&attr);
    exit(0);

}


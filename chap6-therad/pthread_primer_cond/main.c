#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;

static void *thr_func(void *p)
{

    int inNum = (int)(p);

    while (1)
    {
        pthread_mutex_lock(&mut_num);
        while (num == 0)
        {
            // pthread_mutex_unlock(&mut_num);
            // sched_yield();
            // pthread_mutex_lock(&mut_num);
            pthread_cond_wait(&cond_num,&mut_num);
        }
        if (num == -1){
            pthread_mutex_unlock(&mut_num);
            break;
        }
        int tskNum = num;
        num = 0;
        pthread_cond_broadcast(&cond_num);
        pthread_mutex_unlock(&mut_num);
        int j,mark = 1;
        for ( j = 2; j < tskNum / 2; j++)
        {
            if (tskNum % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if (mark){
            printf("thread[%d] compute %d is a primer \n",inNum,tskNum);
        }
        
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid[THRNUM];
    for (int i = 0; i < THRNUM; i++)
    {
        int err = pthread_create(tid + i, NULL, thr_func, (void *)i);
        if (err)
        {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            exit(1);
        }
    }
    for (int j = LEFT; j <= RIGHT; j++)
    {
        pthread_mutex_lock(&mut_num);
        while (num != 0)
        {
            // pthread_mutex_unlock(&mut_num);
            // sched_yield();
            // pthread_mutex_lock(&mut_num);
            pthread_cond_wait(&cond_num,&mut_num);
        }
        num = j;
        pthread_cond_broadcast(&cond_num);
        pthread_mutex_unlock(&mut_num);
    }
    pthread_mutex_lock(&mut_num);
    while(num != 0){
        // pthread_mutex_unlock(&mut_num);
        // sched_yield();
        // pthread_mutex_lock(&mut_num);
        pthread_cond_wait(&cond_num,&mut_num);
    }
    num = -1;
    pthread_cond_broadcast(&cond_num);
    pthread_mutex_unlock(&mut_num);
    for (int i = 0; i < THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mut_num);
    pthread_cond_destroy(&cond_num); //销毁条件变量
    exit(0);
}

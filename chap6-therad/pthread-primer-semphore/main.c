#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "mysem.h"

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT - LEFT + 1)
#define N 4

struct thr_arg_st
{
    int n;
    int resp; //返回值
};

static mysem_t *sem;

static void *is_prime(void *num)
{
    // 0 非素数，1 为素数
    int inNum = ((struct thr_arg_st *)num)->n;

    int retNum = 0;
    if (inNum < 2)
    {
        ((struct thr_arg_st *)num)->resp = 1;
        mysem_add(sem, 1);
        pthread_exit(num);
    }
    for (int j = 2; j < inNum / 2; j++)
    {
        if (inNum % j == 0)
        {
            ((struct thr_arg_st *)num)->resp = 0;
            mysem_add(sem, 1);
            pthread_exit(num);
        }
    }
    ((struct thr_arg_st *)num)->resp = 1;
    sleep(3);
    mysem_add(sem, 1);
    pthread_exit(num);
}

int main()
{

    int i;
    pthread_t tid[RIGHT - LEFT + 1];
    sem = mysem_init(N);
    if (sem == NULL){
        fprintf(stderr,"mysem_init(): %s\n",strerror(sem));
        exit(1);
    }
    struct thr_arg_st *p;
    for (i = LEFT; i <= RIGHT; i++)
    {
        mysem_sub(sem, 1);
        p = malloc(sizeof(*p));
        p->n = i;
        int err = pthread_create(&tid[i - LEFT], NULL, is_prime, p);
        if (err)
        {
            fprintf(stderr, "phtread_create(): %s\n", strerror(err));
            exit(1);
        }
    }
    for (i = LEFT; i <= RIGHT; i++)
    {
        struct thr_arg_st *ptemp;
        pthread_join(tid[i - LEFT], &ptemp);
        if (ptemp->resp == 1)
        {
            fprintf(stdout, "in main , num %d is prime \n", i);
        }
        free(ptemp);
    }
    mysem_destroy(sem);
    exit(0);
}

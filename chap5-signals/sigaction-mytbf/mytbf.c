#include <stdio.h>
#include <stdlib.h>

#include <mytbf.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h> 
#include <sys/time.h>

static struct mytbf_st* job[MYTBF_MAX];

static int inited = 0; 

static struct sigaction alrm_sa_save; //保存的信号处理器

//typedef void(*sighandler_t)(int);

//static sighandler_t alrm_handler_save;

struct  mytbf_st
{
    int cbs;
    int burst;
    int token;
    int pos;

};


static int get_free_pos(void) {
    for (int i = 0;i<MYTBF_MAX;i++){
        if (job[i] == NULL){
            return i;
        }
    }
    return -1;
}

static void alrm_action(int s,siginfo_t *infop,void* unused){
    //alarm(1);
    if (infop->si_code != SI_KERNEL){
        return; //仅仅响应来自内核的信号
    }
    struct itimerval itv;
    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec= 0;
    setitimer(ITIMER_REAL,&itv,NULL);

    for(int i =0;i< MYTBF_MAX;i++){
        if(job[i] != NULL){
            job[i]->token = job[i]->token + job[i]->cbs;
            if (job[i]->token > job[i]->burst){
                job[i]->token = job[i]->burst;
            }
        }
    }
}
static void module_load(void ){
    //alrm_handler_save = signal(SIGALRM,alrm_handler);
    //alarm(1);
    struct sigaction sa;
    sa.sa_sigaction = alrm_action;
    sigempty(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGALRM,&sa,&alrm_sa_save);
    struct itimerval itv;
    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec= 0;
    setitimer(ITIMER_REAL,&itv,NULL);
    
    atexit(module_unload);
}

static void module_unload(void){
    // signal(SIGALRM,alrm_handler_save);
    // alarm(0);

    sigaction(SIGALRM,&alrm_sa_save,NULL);
    struct itimerval itv;
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec= 0;
    setitimer(ITIMER_REAL,&itv,NULL);

    for (int i =0;i<MYTBF_MAX;i++){
        free(job[i]);
    }
}

mytbf_t  *mytbf_init(int cps,int burst){
    struct mytbf_st  *me;
    if (!inited){
        module_load();
        inited = 1;
    }
    int pos;
    pos = get_free_pos();
    if (pos < 0) {
        return NULL;
    }
    me = malloc(sizeof(*me));
    if (me == NULL){
        return NULL;
    }
    me->token = 0;
    me->burst = burst;
    me->cbs = cps;
    me->pos = pos;
    job[pos] = me;
    return me; 
}

int mytbf_fetchtoken(mytbf_t *ptr,int size){
    if (size <= 0){
        return -EINVAL;
    }
    struct mytbf_st  *me = ptr;
    while (me->token <= 0)
    {
        pause();
    }
    int n;
    n = min(me->token,size);
    me->token -= n;
    return n;
    
}

static int min(int a,int b){
    if(a<b){
        return a;
    }
    return b;
}
int mytbf_returntoken(mytbf_t *ptr,int size){
    if (size <= 0){
        return -EINVAL;
    }
    struct mytbf_st  *me = ptr;
    me->token += size;
    if(me->token > me->burst){
        me->token = me->burst;
    }
    return size;
}

int mytbf_destroy(mytbf_t *ptr){
    struct mytbf_st *me = ptr;
    job[me->pos] = NULL;
    free(ptr);
    return 0;
}
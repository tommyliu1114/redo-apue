#include <stdio.h>
#include <stdlib.h>

#include <mytbf.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h> 

static struct mytbf_st* job[MYTBF_MAX];

static int inited = 0; 

typedef void(*sighandler_t)(int);

static sighandler_t alrm_handler_save;

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

static void alrm_handler(int s){
    alarm(1);
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
    alrm_handler_save = signal(SIGALRM,alrm_handler);
    alarm(1);
    atexit(module_unload);
}

static void module_unload(void){
    signal(SIGALRM,alrm_handler_save);
    alarm(0);
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
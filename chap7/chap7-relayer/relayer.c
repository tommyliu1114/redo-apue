#include "relayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <errno.h>
#include <pthread.h> 
#include <string.h>
enum {
    STATE_R = 1,
    STATE_W,
    STATE_EX,
    STATE_T 
};

struct rel_fsm_st {
    int state; //当前状态机状态
    int sfd;
    int dfd;
    char buff[BUFSIZ];
    int len ;
    int pos ;
    char *errstr;
    int count;
};

struct rel_job_st {
    int fd1;
    int fd2;
    int job_state;
    struct rel_fsm_st fsm12,fsm21;
    int fd1_save,fd2_save;
};

static struct rel_job_st* rel_job[REL_JOBMAX];
static pthread_mutex_t mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void fsm_driver(struct rel_fsm_st *fsm){
    ssize_t ret ;
    switch (fsm->state)
    {
    case STATE_R:
        fsm->len = read(fsm->sfd,fsm->buff,BUFSIZ);
        if (fsm->len == 0){
            fsm->state = STATE_T;
        }else if (fsm->len < 0){
            if (errno == EAGAIN){
                fsm->state = STATE_R;
            }else {
                fsm->errstr = "read()";
                fsm->state = STATE_EX;
            }
        }else{
            fsm->state = STATE_W;
            fsm->pos = 0;

        }
        break;
    case STATE_W:
        
        ret = write(fsm->dfd,fsm->buff+fsm->pos,fsm->len);
        if (ret < 0){
            if (errno == EAGAIN){
                fsm->state = STATE_W;
            }else{
                fsm->errstr = "write()";
                fsm->state = STATE_EX;
            }
        }else{
            fsm->pos += ret;
            fsm->len -= ret;
            if (fsm->len == 0){
                fsm->state = STATE_R;
            }else{
                fsm->state = STATE_W;
            }
        }
        break;
    case STATE_EX:
        perror(fsm->errstr);
        fsm->state = STATE_T;
        break;
    case STATE_T:
        break;
    default:
        break;
    }
}

static int get_free_pos_unlocked(){
    for(int i = 0;i<REL_JOBMAX;i++){
        if(rel_job[i] == NULL){
            return i;
        }
    }
    return -1;
}

static void *thr_relayer(void *p){
    while (1)
    {
    pthread_mutex_lock(&mut_rel_job);
    for(int i = 0;i<REL_JOBMAX;i++){
        if (rel_job[i] != NULL){
            if(rel_job[i]->job_state == STATE_RUNNING){
                               fsm_driver(&rel_job[i]->fsm12);
                fsm_driver(&rel_job[i]->fsm21);
                if (rel_job[i]->fsm12.state == STATE_T && rel_job[i]->fsm21.state == STATE_T ){
                    rel_job[i]->job_state = STATE_OVER;
                }
            }
        }
    }
    pthread_mutex_unlock(&mut_rel_job);
    }

    
}
static void module_load(void){
    pthread_t tid_relayer;
    int err = pthread_create(&tid_relayer,NULL,thr_relayer,NULL);
    if(err){
        fprintf(stderr,"pthread_create(): %s\n",strerror(err));
        exit(1);
    }
}



int rel_addjob(int fd1,int fd2){
    pthread_once(&init_once,module_load);
    struct rel_job_st *me;
    me = malloc(sizeof(*me));
    if (me == NULL){
        return -ENOMEM;
    }
    me->fd1 = fd1;
    me->fd2 = fd2;
    me->job_state = STATE_RUNNING;
    me->fd1_save = fcntl(me->fd1,F_GETFL);
    fcntl(me->fd1,F_SETFL,me->fd1_save | O_NONBLOCK);
    me->fd2_save = fcntl(me->fd2,F_GETFL);
    fcntl(me->fd2,F_SETFL,me->fd2_save | O_NONBLOCK);  
    me->fsm12.sfd = me->fd1;
    me->fsm12.dfd = me->fd2;
    me->fsm12.state = STATE_R;

    me->fsm21.sfd = me->fd2;
    me->fsm21.dfd = me->fd1;
    me->fsm21.state = STATE_R;
    pthread_mutex_lock(&mut_rel_job);
    int pos = get_free_pos_unlocked();
    if (pos < 0){
        pthread_mutex_unlock(&mut_rel_job);
        fcntl(me->fd1,F_SETFL,me->fd1_save);
        fcntl(me->fd2,F_SETFL,me->fd2_save);
        free(me);
        return -ENOSPC;
    }
    rel_job[pos] = me;
    pthread_mutex_unlock(&mut_rel_job);

}
/*
    return >= 0 成功，返回当前人物id
           == -EINVAL 失败参数非法
           == -ENOSPC 失败，任务数组满
           == -ENOMEM 失败，内存分配有误
*/
int rel_canceljob(int id);
/*
    return == 0 成功，取消任务成公
           == -EINVAL 失败，参数非法
           == -EBUSY 失败，任务已被取消

*/
int rel_waitjob(int id,struct rel_stat_st *);
/*
    return == 0 成功，指定人物已经终止，并返回状态
           == -EINVAL 失败，参数非法
*/

int rel_statjob(int it,struct  rel_stat_st *);


#ifndef RELAYER_H__
#define RELAYER_H__

#define REL_JOBMAX 500 

enum {
    STATE_RUNNING = 1,
    STATE_CANCELED ,
    STATE_OVER
};
struct rel_stat_st {
    int state;
    int fd1;
    int fd2;
    int  count12,count21;

    //struct timeval start,end;
};

int rel_addjob(int fd1,int fd2);
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



#endif
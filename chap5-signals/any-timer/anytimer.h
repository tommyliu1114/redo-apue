#ifndef ANYTIMER_H__
#define ANYTIMER_H__
#define ANYTIMER_MAX 1024
typedef void at_jobfunc_t(void*);
int at_addjob(int sec, at_jobfunc_t *jobp,void *arg);
/*
    return >= 0 成功
           == -EINVAL 失败
           == -ENOSPC 失败，数组满了
           == -ENOMEM 失败，无内存空间  
*/
int at_canceljob(int id);
/*
    return == 0 成功，指定任务取消
           == -ENIVAL 失败，参数非法
           == -EBUSY 失败，指定任务已经完成
           == -ECANCELED 失败，指定任务重复取消  
*/
int at_waitjob(int id);
/*
    return == 0 成功，指定任务成功释放
           == -EINVAL 失败，参数非法
           
*/
#endif 
# 线程  
+ 一个正在运行的函数（线程）：posix线程是一套标准，而不是实现。openmp线程
+ 线程的概念
    - 线程的标识： pthread_t  
    - pthread_equal: 比较两个线程号 ，
    - pthread_self: 获取当前线程的标识；
+ 线程的创建：
    - pthread_create: 线程调度取决于调度器的调度策略 
+ 线程的终止：3中方式 
    - 线程从启动的例程中返回，返回值就是线程的退出码
    - 线程可以被同一进程中的其他线程取消
    - 线程调用pthread_exit()函数，相当于进程阶段的exit，仅仅结束当前运行的线程
    - pthread_join   : 相当于wait原语
+ 线程的取消选项 : pthread_cancel(): 取消有两种状态：允许和不允许
    - 允许取消： 异步cancel，推迟cancel（默认)推迟至cancel点
    - cancel点： posix定义的cancle点为引发阻塞的系统调用 
        - pthread_setcancelstatue(): 设置是否允许取消
        - pthread_setcanceltype(): 设置取消方式，异步还是cancel
        - pthread_testcancel(): 本函数啥都不做，就是一个取消点  
+ 线程的分离： pthread_detach() : 

+ 线程的清理:
    - pthread_cleanup_push() : 
    - pthread_cleanup_pop() 
+ 线程同步 : 
    - 互斥量类型： pthread_mutex_t 
    - 互斥量 ： pthread_mutex_init()  pthread_mutex_destroy 
    - 互斥量使用： pthread_mutex_lock()  pthread_mutex_unlock()  pthread_mutex_trylock()  
    - pthread_once: 仅仅执行一次

    - pthread_cond_t ，pthread_cond_init, pthread_cond_destroy, 
    - pthread_cond_broadcast, pthread_cond_signal 
    - pthread_cond_timewait, pthread_cond_wait ,
    
+ 线程属性  
+ 线程同步的属性
+ 线程与信号
+ 线程与fork
+ 线程的可重入  
+ 
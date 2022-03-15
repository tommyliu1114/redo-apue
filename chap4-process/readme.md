# process 的基本知识  
 
+ 进程标识符pid ：
    - 类型： pid_t 
    - 命令： ps    
    - 进程号顺次向下使用  
    - getpid（），getppid（），获取进程号，父进程号；
+ 进程的产生：    
    - fork（） :fork后父子进程的区别，fork的返回值不一样，pid不同，ppid也不同，未决信号和文件锁不继承，资源利用量清零；
    - init进程： 所有进程的祖先进程， 
    - 调度器的调度策略，决定哪个进程先运行，
    - fork前fflush的重要性    
    - vfork（）：淘汰  
+ 进程的消亡及释放资源：  wait()死等;waitpid()可以通过options来控制等待的行为;waitid(); 
+ 进程池的实现；
+ exec函数族：   execl,execlp,execle,execv,execvp 
+ 用户权限以及组权限：   
+ system函数：  
+ 进程会计：  
+ 进程时间：   
+ 守护进程：  
+ 系统日志：  
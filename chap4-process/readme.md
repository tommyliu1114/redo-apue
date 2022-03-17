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
+ 用户权限以及组权限： 粘连位， u+s ; g+s; uid:real userid :真实的用户🆔id ,effective userid 有效的用户🆔id，鉴权exec执行时候使用；save userid 
    - getuid 获取真实🆔id
    - geteuid 获取有效🆔id
    - getgid 
    - getegid 
    - setuid 设置设置effective user id 
    - setgid 
    - setreuid 交换真实🆔id和有效🆔id，原子化的
    - setregid 
+ system函数：  fork+exec 封装
+ 进程会计：  acct 
+ 进程时间：   times();
+ 守护进程：  
    - 会话 session,会话标识sid , 
    - 终端 
    - setsid : 非leader的进程调用，必须子进程调用。常用做法：子进程执行，父进程退出，自动成为守护在后台运行
    - getpgid
    - getpgrp 
+ 系统日志：  
    - syslogd服务,openlog(); syslog();closelog();
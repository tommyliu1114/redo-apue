# 并发
- 同步
- 异步
- 异步事件的处理： 查询法，通知法
- 信号
    + 信号的概念： 信号是软件中断;信号的响应依赖于中断  
    + signal: signal(int signum,void (*func)(int)) 信号会打断阻塞的系统调用
    + 信号的不可靠 ： 标准信号会丢失，实时信号不会丢失。信号的行为不可靠
    + 可重入函数： 为解决信号不可靠，第一次调用为结束，第二次调用也发生了，但是不会报错。注意： 所有的系统调用都是可重入的，一部分库函数也是可重入的。  
    + 信号的响应过程 : mask和pending。信号从手到到响应有延迟。如何忽略掉一个信号的。标准信号为何会丢失。mask和pending按位置与操作的时机仅仅出现在从内核态到用户态切换，所以这个时候才会发现信号。所以信号依赖于中断的实现。标准信号的响应没有严格的顺序。 
    + 常用函数：
        - kill 
        - raise 给自己发信号，可以给进程/线程发信号（有多态的感觉） 
        - alarm  下发SIGALARM信号,令牌桶实现
        - pause 等待信号,不是轮询等，是事件机制的
        - setitimer(): getitimer 
        - abort
        - system
        - sleep,nanosleop,usleep 
    + 信号集: 
        - sigemptyset 
        - sigfillset
        - sigaddset 
        - sigdelset 
        - sigismember 
    + 信号屏蔽字/pending集合的处理:
        - sigprocmask(); 人为的控制信号响应
        - sigpending: 
    + 扩展：
        - sigsuspend: todo 重要，信号驱动程序
        - sigaction: 避免了signal信号处理中的信号重入,替换sigaction函数即可
        - setitimer： 设置定时器；
    + 实时信号： 标准信号放在位图中处理，可能会丢失。标准信号优先响应，实时信号后面响应；
        - 排队处理：ulimit -a 可以查看pengding-signals查看最多排队多少个信号
        - 不会丢失
- 线程

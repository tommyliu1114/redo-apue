# process terminal 
- normal  
    + return from main function 
    + exit
    + _exit or _Exit 
    + last thread return from start routine 
    + last thread call pthread_exit

- abnormal 
    + abort
    + receive singnal and terminate 
    + last thread response to the cancel request 

# atexit() : hooker function 

# pmap  
# so 
# lib 
# hand-load-libs : plugins implements 
- dlopen  
- dlclose
- dlsym 
# setjmp()  set jmp point
# longjmp()  jmp to point  
# getrlimit()  get resorese limits  
# setrlimit()  set resource limits  
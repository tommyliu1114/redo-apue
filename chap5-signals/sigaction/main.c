#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#define FNAME "/tmp/out"

static  FILE *fp;
static int deamonize(void)
{
    pid_t pid;
    int fd;
    pid = fork();
    if (pid < 0)
    {
        return -1;
    }
    if (pid > 0)
    {
        exit(0);
    } //父进程退出
    fd = open("/dev/null", O_RDWR);
    if (fd < 0)
    {
        return -1;
    }
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > 2)
    {
        close(fd);
    }
    setsid();
    chdir("/");
    // umask(0);
    return 0;
}

static void daemon_exit(int sig){
    fclose(fp);
    closelog(); //关闭日志文件；
    exit(0);
}




int main()
{
   
    // signal(SIGINT,daemon_exit);
    // signal(SIGQUIT,daemon_exit);
    // signal(SIGTERM,daemon_exit);
    struct sigaction sa;
    sa.sa_handler = daemon_exit;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask,SIGQUIT);
    sigaddset(&sa.sa_mask,SIGTERM);
     sigaddset(&sa.sa_mask,SIGINT);
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);

    struct sigaction sb;
    sb.sa_handler = daemon_exit;
    sigemptyset(&sb.sa_mask);
    sigaddset(&sb.sa_mask,SIGINT);
    sigaddset(&sb.sa_mask,SIGTERM);
    sigaddset(&sb.sa_mask,SIGQUIT);
    sb.sa_flags = 0;
    sigaction(SIGQUIT,&sb,NULL);


    struct sigaction sc;
    sc.sa_handler = daemon_exit;
    sigemptyset(&sc.sa_mask);
    sigaddset(&sc.sa_mask,SIGINT);
    sigaddset(&sc.sa_mask,SIGQUIT);
    sigaddset(&sc.sa_mask,SIGTERM);
    sc.sa_flags = 0;
    sigaction(SIGTERM,&sc,NULL);

    openlog("chap4deamon",LOG_PID,LOG_DAEMON);
    if (deamonize()){
        syslog(LOG_ERR,"daemonize() failed!");
        exit(1);
    }else{
        syslog(LOG_INFO,"daemonize success!");
    }
    fp = fopen(FNAME, "w");
    if (fp == NULL)
    {
        syslog(LOG_ERR,"fopen() file err: %s",strerror(errno));
        exit(1);
    }
    for (int i = 0;; i++)
    {
        fprintf(fp, "%d\n", i);
        fflush(fp);
        sleep(1);
    }
    exit(0);
}

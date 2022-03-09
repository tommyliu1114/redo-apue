#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#define FNAME "/tmp/out"
int main()
{
    FILE *fp;
    int count = 0;
    char buf[BUFSIZ];
    time_t stamp;
    struct tm *tm;
    fp = fopen(FNAME,"a+");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    while(fgets(buf,BUFSIZ,fp) != NULL)
    {
        count++;
    }
    while (1)
    {
        time(&stamp);
        tm = localtime(&stamp);
        fprintf(fp,"%-4d%d-%d-%d %d:%d:%d\n",++count,tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);
        fflush(fp);
        sleep(1);
        if (count == 20)
        {
            break;
        }
    }
    fclose(fp);
    exit(0);
    
    /*
    time_t stamp;
    struct tm *tm;
    time(&stamp);
    stamp = time(NULL);
    tm = localtime(&stamp);
    strftime(buf,BUFSIZ,"%Y-%m-%d",tm);
    puts(buf);
    */

}
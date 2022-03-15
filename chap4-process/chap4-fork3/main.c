#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LEFT 30000000
#define RIGHT 30000200
#define N 3

int main()
{

    int i, j, mark, n;
    pid_t pid;
    for (n = 0; n < N; n++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1); // todo gaijin
        }
        if (pid == 0)
        {
            //子进程
            for (i = LEFT+n; i <= RIGHT; i+=N)
            {
                mark = 1;
                for (j = 2; j < i / 2; j++)
                {
                    if (i % j == 0)
                    {
                        mark = 0;
                        break;
                    }
                }
                if (mark == 1)
                {
                    printf("[%d]%d is a primer \n", n,i);
                }
            }
            exit(0);
        }
        else
        {
        }
    }
    int st;
    for (n = 0; n < N; n++){
        wait(&st);
    }
    exit(0);
}
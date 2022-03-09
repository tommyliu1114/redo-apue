#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void f1(void) 
{
    puts("f1() is working!");
}

static void f2(void)
{
    puts("f2() is working!");
}

static void f3(void)
{
    puts("f3() is working1");
}

int main(int argc,char **argv)
{
    puts("begin!");
    atexit(f1);
    atexit(f2);
    atexit(f3);
    puts("main end!");
    exit(0);
}
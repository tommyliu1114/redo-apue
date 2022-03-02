#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(){
    FILE *fp;
    fp = fopen("tmp","r");
    if (fp == NULL){
        fprintf(stderr,"fopen(): failed,errno = %d\n",errno);
        exit(1);
    }
    puts("ok");
    exit(0);
}
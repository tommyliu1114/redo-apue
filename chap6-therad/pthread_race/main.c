#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define THRNUM 20 
#define FNAME "/tmp/out"
#define LINESIZE 1024

static void* thr_add(void* p) {
    char linebuf[LINESIZE];
    FILE *fp = fopen(FNAME,"r+");
    if(fp ==NULL){
        perror("fopen()");
        pthread_exit(NULL);
    }
    fgets(linebuf,LINESIZE,fp);
    fseek(fp,0,SEEK_SET);
    fprintf(fp,"%d\n",atoi(linebuf)+1);
    fclose(fp);
    pthread_exit(NULL);

}

int main(){
    pthread_t tid[THRNUM];
    for (int i =0;i<THRNUM;i++){
        int err = pthread_create(tid+i,NULL,thr_add,NULL);
        if (err){
            fprintf(stderr,"pthread_create(): %s\n",strerror(err));
            exit(1);
        }
    }
    for (int i =0;i<THRNUM;i++){
        pthread_join(tid[i],NULL);
    }
 
    exit(0);

}


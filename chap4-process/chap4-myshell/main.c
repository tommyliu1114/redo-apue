#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <glob.h> 

#define DELIMS " \t\n"

struct cmd_st {
    glob_t globres;
};
static void prompt(void){
    printf("myshell-0.1$ ");
}

static void parse(char* linebuf, struct cmd_st *cmd ){
    char *tok;
   
    int i = 0;
    while (1)
    {
         tok = strsep(&linebuf,DELIMS);
         if (tok == NULL){
             break;
         }
         if(tok[0]== '\0'){
             continue;
         }
         glob(tok,GLOB_NOCHECK|GLOB_APPEND*i,NULL,&cmd->globres);
         i = 1;
    }
    
   
}
int main(){
    char *linebuf = NULL;
    size_t linebuf_size = 0;
    struct cmd_st cmd;
    pid_t pid;
    while (1)
    {
        prompt();
       if( getline(&linebuf,&linebuf_size,stdin) < 0){
           break;
       }
        parse(linebuf,&cmd);
        if(0){

        }else{
            pid = fork();
            if (pid< 0){
                perror("fork()");
                exit(1);
            }else if ( pid == 0 ){
                execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
                perror("execvp");
                exit(1);
            }else{
                wait(NULL);
            }
        }
    }
    
}
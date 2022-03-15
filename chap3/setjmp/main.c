#include <stdio.h> 
#include <stdlib.h> 
#include <setjmp.h>
static jmp_buf save;
static void c(void) {
    printf("%s():Begin.\n",__FUNCTION__);
    //printf("%s():call c().\n",__FUNCTION__);
    //c();
     //printf("%s():c()) returned.\n",__FUNCTION__);
    printf("%s(): jump now!\n",__FUNCTION__);
    longjmp(save,6);
    printf("%s():call End.\n",__FUNCTION__);   
    //exit(0);    
}

static void b(void) {
    printf("%s():Begin.\n",__FUNCTION__);
    printf("%s():call c().\n",__FUNCTION__);
    c();
     printf("%s():c() returned.\n",__FUNCTION__);
    printf("%s():call End.\n",__FUNCTION__);   
    //exit(0);    
}


static void a(void) {
    int ret;
    
    printf("%s():Begin.\n",__FUNCTION__);
    ret = setjmp(save);
    if (ret == 0 )
    {
        printf("%s():call b().\n",__FUNCTION__);
        b();
        printf("%s():b() returned.\n",__FUNCTION__);
    }else{
        printf("%s(): jumped back here with code %d\n",__FUNCTION__,ret);
    }
    printf("%s():call End.\n",__FUNCTION__);   
    //exit(0);    
}

int main()
{
    printf("%s():Begin.\n",__FUNCTION__);
    printf("%s():call a().\n",__FUNCTION__);
    a();
     printf("%s():a() returned.\n",__FUNCTION__);
    printf("%s():call End.\n",__FUNCTION__);   
    exit(0);
}
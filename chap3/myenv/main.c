#include <stdio.h>
#include <stdlib.h>

extern char **environ ;

int main()
{
    int i ;
    for (i=0;environ[i] != NULL; i++)
    {
        puts(environ[i]);
        puts("---------------------");
    }
    char* langV;
    langV = getenv("LANG");
    if (langV != NULL )
    {
        puts("==========================");
        puts(langV);
    }
    exit(0);
}
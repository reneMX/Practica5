#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv){

    printf("Proceso Resta\n");
    printf("%s : %d \n ", argv[0], getpid());
    for(int i = 0; i <  argc ; i ++)
    {
        printf("Argumento %d,  %s\n", i, argv[i]);
    }
    while(1);

return 0;
}//fin main
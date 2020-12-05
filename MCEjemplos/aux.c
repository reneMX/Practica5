
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "memoria.h"

int main(int argc, char **argv[]){

    key_t Clave;
    int ID;
    struct Memoria *ptr;


    
    Clave = ftok(argv[0], atoi(argv[1]) );
    //printf("Valores de la clave en proceson Suma: char*: %s | int: %c\n",argv[0],atoi(argv[1]) );
    ID = shmget(Clave, sizeof(struct Memoria), 0666 );

    if(Clave < 0){
        printf("***Cliente: error en shmget\n");
        exit(1);
    }
    printf("Cliente: Recibiendo memoria compartida\n");

    ptr = (struct Memoria *) shmat(ID, NULL, 0 );
    if( ((int)ptr) == -1 )
    {
        printf("***Cliente: ERROR!!, en shmat\n ");
        exit(1);
    } 

    printf("Cliente: Accediendo a memoria compartida\n");

    while( ptr->estado != LLENO )
        ;

    printf("Cliente: Leyendo datos.\n");
    printf("Cliente: Los datos son %f, %f\n", ptr->operando_1, ptr->operando_2 );
   // ptr->resultado = ptr->operando_1 + ptr->operando_2;
    ptr->estado = RECIBIDO;
    printf("Estado %d\n", ptr->estado);
    printf("Cliente: Enviando confirmacion de recibido.\n");
    shmdt( (void*) ptr );
    printf("Cliente: Liberando Memoria\n");
    printf("Cliente: Terminado\n");    
    
return 0;
}//fin main
         
         /*
            //CASO - //
            case '-':
                pid = fork();
                if( pid == 0 )
                {
                    //printf("Soy el proceso  hijo %d\n", getpid());    
                    sleep(5);
                    execv("./resta", arvg2_resta);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                }
                while(1);
                //printf("Para clonar - \n");
            break;

            //CASO x //
            case 'x':
                pid = fork();
                if( pid == 0 )
                {
                    //printf("Soy el proceso  hijo %d\n", getpid());                  
                    sleep(5);
                    execv("./multi", arvg2_multi);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                }
                while(1);                
                //printf("Para clonar x \n");
            break;

            //CASO / //
            case '/':
                pid = fork();
                if( pid == 0 )
                {
                    //printf("Soy el proceso  hijo %d\n", getpid());    
                    sleep(5);
                    execv("./division", arvg2_div);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                }
                while(1);                
                //printf("Para clonar / \n");
            break;
            
            //CASO # //
            case '#':
                for ( int i = 0 ; i < 4 ; i++ )
                {
                    pid = fork();
                    if( pid == 0)
                    {
                        sleep(5);
                        switch (i)
                        {
                            //CASO DOND i = 0//
                            case 0:                                                         
                                execv("./suma", arvg2_suma);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                            break ;

                            //CASO DOND i = 1//
                            case 1:
                                execv("./resta", arvg2_resta);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                            break ;

                            //CASO DOND i = 2//
                            case 2:
                                execv("./multi", arvg2_multi);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                            break ;

                            //CASO DOND i = 3//
                            case 3:
                                execv("./division", arvg2_div);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                            break ;
                        }
                        break;
                    }
                }
            break;  

            */
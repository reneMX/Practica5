#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "memoria.h"

int main(int argc, char *argv[]){

    key_t Clave;
    int ID;
    struct Memoria *ptr;

    printf("\n\n\nPROCESO MULTIPLICACION\n");
    printf("argv1 %s\n", argv[0]);
    printf("argv1 %d\n", atoi(argv[1]));
    printf("\n\n....espera un momento para ver el arbol\n");
    sleep(10);
    
    
    Clave = ftok(argv[0], atoi(argv[1]) );
    ID = shmget(Clave, sizeof(struct Memoria), 0666 );

    if(Clave < 0){
        ptr->mensaje_error = "***multi: error en shmget\n" ;
        //printf("***multi: error en shmget\n");
        exit(1);
    }
    printf("multi: Recibiendo memoria compartida\n");

    ptr = (struct Memoria *) shmat(ID, NULL, 0 );
    if( ((int)ptr) == -1 )
    {
       // printf("***multi: ERROR!!, en shmat\n ");
        ptr->mensaje_error = "***multi: ERROR!!, en shmat\n " ;
        exit(1);
    } 

    printf("multi: Accediendo a memoria compartida\n");

    while( ptr->estado != LLENO )
        ;
    ptr->resultado = ptr->operando_1 * ptr->operando_2; 
    printf("multi: Leyendo datos.\n");
    printf("multi: Los datos son %f, %f, %f\n", ptr->operando_1, ptr->operando_2, ptr->resultado);
   
    ptr->estado = RECIBIDO;
    printf("multi: Enviando confirmacion de recibido.\n");
    shmdt( (void*) ptr );
    printf("multi: Liberando Memoria\n");
    printf("multi: Terminado\n");    


    
return 0;
}//fin main
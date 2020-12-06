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
    
    
    Clave = ftok(argv[0], atoi(argv[1]) );
    ID = shmget(Clave, sizeof(struct Memoria), 0666 );

    
    printf("\n\n\nPROCESO RESTA\n");
    printf("\n\nresta: ....espera un momento para ver el arbol\n");
    
    
    if(Clave < 0){
        printf("***resta: error en shmget\n");
        exit(1);
    }
    printf("resta: Recibiendo memoria compartida\n");

    ptr = (struct Memoria *) shmat(ID, NULL, 0 );
    if( ((int)ptr) == -1 )
    {
        printf("***resta: ERROR!!, en shmat\n ");
        exit(1);
    } 

    printf("resta: Accediendo a memoria compartida\n");

    while( ptr->estado != LLENO )
        ;
    ptr->resultado = ptr->operando_1 - ptr->operando_2; 
    printf("resta: Leyendo datos.\n");
    printf("resta: Los datos son %f, %f, %f\n", ptr->operando_1, ptr->operando_2, ptr->resultado);
   
    ptr->estado = RECIBIDO;
    printf("resta: Enviando confirmacion de recibido.\n");
    shmdt( (void*) ptr );
    printf("resta: Liberando Memoria\n");
    printf("resta: Terminado\n");    

    sleep(5);   
    
return 0;
}//fin main
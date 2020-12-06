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
   
   
    printf("\n\n\nPROCESO SUMA\n");
    printf("\n\nsuma: ....espero un momento para que puedas ver el arbol\n");
    
    
   

    if(Clave < 0){
        printf("***suma: error en shmget\n");
        exit(1);
    }
    printf("suma: Recibiendo memoria compartida\n");

    ptr = (struct Memoria *) shmat(ID, NULL, 0 );
    if( ((int)ptr) == -1 )
    {
        printf("***suma: ERROR!!, en shmat\n ");
        exit(1);
    } 

    printf("suma: Accediendo a memoria compartida\n");

    while( ptr->estado != LLENO )
        ;
    ptr->resultado = ptr->operando_1 + ptr->operando_2; 
    printf("suma: Leyendo datos.\n");
    printf("suma: Los datos son %f, %f, %f\n", ptr->operando_1, ptr->operando_2, ptr->resultado);
   
    printf("suma: Pasamos a estado RECIBIDO\n");
    ptr->estado = RECIBIDO;
    printf("suma: Enviando confirmacion de recibido.\n");
    shmdt( (void*) ptr );
    printf("suma: Liberando Memoria\n");
    printf("suma: Terminado\n");    

       
return 0;
}//fin main
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


#include "memoria.h"

int main(int argc, char *argv[]){

    key_t Clave;
    int ID;
    struct Memoria *ptr;

    //Clave = ftok(".",'x');
    printf("argv1 %s\n", argv[0]);
    printf("argv1 %d\n", atoi(argv[1]));
    printf("\n\n....espera un momento para ver el arbol\n");
    sleep(10);
    
    Clave = ftok(argv[0], atoi(argv[1]));
    ID = shmget( Clave, sizeof(struct Memoria), 0666);
    
    if( Clave < 0 ){
        printf("***Cliente: error en shmget\n");
        exit(1);
    }
    printf("Cliente: Recibiendo memoria compartida\n");

    ptr = (struct Memoria *) shmat( ID, NULL, 0);
    if( (int) ptr == -1 )
    {
        printf("***Cliente: ERROR!!!, en shmat\n");
        exit(1);
    }
    printf("Cliente: Accediendo a memoria compartida\n");

    while( ptr->estado != LLENO )
        ;
    ptr->resultado = ptr->operandoA + ptr->operandoB ;
    printf("Cliente: Leyendo datos.\n");
    printf("Cliente: Los datos son %f, %f, %f\n", ptr->operandoA, ptr->operandoB, ptr->resultado);

    ptr->estado = RECIBIDO;
    
    printf("Cliente: Enviando confirmacion de recibido.\n");
    shmdt( (void*) ptr );
    printf("Cliente: Liberando Memoria\n");
    printf("Cliente: Terminado\n");    

return 0;    
}

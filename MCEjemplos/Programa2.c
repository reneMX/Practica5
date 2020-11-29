#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "memoria.h"

int main(void){

    key_t Clave;
    int ID;
    struct Memoria *ptr;

    Clave = ftok(".",'x');
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
    printf("Cliente: Leyendo datos.\n");
    printf("Cliente: Los datos son %d, %d, %d, %d.\n", ptr->datos[0], ptr->datos[1], ptr->datos[2], ptr->datos[3]);

    ptr->estado = RECIBIDO;
    printf("Cliente: Enviando confirmacion de recibido.\n");
    shmdt( (void*) ptr );
    printf("Cliente: Liberando Memoria\n");
    printf("Cliente: Terminado\n");    

return 0;    
}

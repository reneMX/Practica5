#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

#include "memoria.h"
int main(int argc, char *argv[] )
{


    key_t Clave;
    int ID;
    struct Memoria *ptr;

    if(argc != 5){
        printf("Proceso 1: Faltan argumentos, por favor escriba los datos a compartir\n");
        exit(1);
    }

    printf("Proceso 1: Id es %d\n", (int) getpid());
    Clave = ftok(".", 'x');
    ID    = shmget(Clave, sizeof(struct Memoria), IPC_CREAT | 0666);
    
    if( ID < 0 )
    {
        printf("***ERROR!!, en shmget (Proceso 1***\n)");
        exit(1);
    }
    printf("Proceso 1: Se utilizara memoria compartida, para almacenar 4 valores enteros\n");

    ptr = (struct Memoria *) shmat( ID, NULL, 0 );//El permiso es 
     if( ((int) ptr ) == -1 )
    {
        printf("***Proceso 1: ERROR!!, en shmat***\n");
        exit(1);
    }
    printf("Proceso 1: Usando la memoria compartida...\n");

    ptr->estado   = NOLISTO;
    ptr->datos[0] = atoi(argv[1]);
    ptr->datos[1] = atoi(argv[2]);
    ptr->datos[2] = atoi(argv[3]); 
    ptr->datos[3] = atoi(argv[4]);

    printf("Proceso 1: Los datos colocados en la memoria compartida son %d, %d, %d, %d\n", ptr->datos[0], ptr->datos[1], ptr->datos[2], ptr->datos[3]);
    ptr->estado = LLENO;

    printf("Proceso 1: Por favor, ejecuta al cliente en otra terminal\n");

    while( ptr->estado != RECIBIDO)
    sleep(5);


    printf("Proceso 1: Se a entregado la informacion...\n");
    shmdt( (void *)ptr );
    shmctl( ID, IPC_RMID, NULL);
    printf("Proceso 1: Liberando memoria compartida\n");
    printf("Proceso 1: Terminado\n");
    return 0;
}
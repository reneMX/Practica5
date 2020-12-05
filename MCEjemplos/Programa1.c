#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "memoria.h"

int main(int argc, char *argv[])
{

    int val ;

    key_t Clave;
    int ID;
    struct Memoria *ptr;

    char *const  arvg2_suma[] = {".","100", NULL};

    pid_t pid;
    char operador = '+';
//.........INCIO PARA CREAR MEMORIA
    printf("Proceso 1: Id es %d\n", (int) getpid());
    Clave = ftok(".", 'd');
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
    ptr->operandoA = 6;
    ptr->operandoB = 7;

    printf("Proceso 1: Los datos colocados en la memoria compartida son %f, %f\n", ptr->operandoA, ptr->operandoB);
    ptr->estado = LLENO;

    printf("Proceso 1: Por favor, ejecuta al cliente en otra terminal\n");

//............COMENSAMOS CON FORK
    val = 0;
    if( operador == '+')
    {
        pid = fork();
        if( pid == 0)
        {
            printf("Soy el %d, mi padre es el %d\n", getpid(), getppid());
            val = val + 2;
        }
    }
printf("En este momento tenemos el proceso hijo\n");
sleep(15);

//.....EN ESTE MOMENTO HACEMOS LA SUSTITUCION Y PASAMOS CLAVE DE MEMORIA COMPARTIDA
    if(val > 0)
    {
        execv("./cliente", arvg2_suma);
    }
    
    while( ptr->estado != RECIBIDO);
    sleep(5);  

    printf("El resultado es %f\n",ptr->resultado);    
    
//..... AQUI SE LIBERA MEMORIA.H
    printf("Proceso 1: Se a entregado la informacion...\n");
    shmdt( (void *)ptr );
    shmctl( ID, IPC_RMID, NULL);
    printf("Proceso 1: Liberando memoria compartida\n");
    printf("Proceso 1: Terminado\n");


     
    











   /* if(argc != 2)
    {
        printf("Proceso 1: Faltan argumentos, por favor escriba los datos a compartir\n");
        exit(1);
    }*/
  
  /*  printf("Proceso 1: Id es %d\n", (int) getpid());
    Clave = ftok(".", 'd');
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
    ptr->operandoA = 6;
    ptr->operandoB = 7;

    printf("Proceso 1: Los datos colocados en la memoria compartida son %f, %f\n", ptr->operandoA, ptr->operandoB);
    ptr->estado = LLENO;

    printf("Proceso 1: Por favor, ejecuta al cliente en otra terminal\n");

    //fork();

    execv("./cliente", arvg2_suma);
    while( ptr->estado != RECIBIDO);
    sleep(5);  


    printf("Proceso 1: Se a entregado la informacion...\n");
    shmdt( (void *)ptr );
    shmctl( ID, IPC_RMID, NULL);
    printf("Proceso 1: Liberando memoria compartida\n");
    printf("Proceso 1: Terminado\n");
*/
    return 0;
 }   
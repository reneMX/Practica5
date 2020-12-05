#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>

#include "memoria.h"




char verificaOperador(char *ope);
void obtenOperandos(char *ando);
void crearMemoriCompartida();
void creaProcesoHijo(char operador);
void sustituyeProceso(char operador);

void convierteTipoOperando(float);
void duplicaProceso(char operador);
void muestraResultado(char operador);


//char *operandos = NULL;
char *const  datos_clave[] = {".","100", NULL};
//char *const  arvg2_resta[] = {"resta", "Sustituido", "Restar", NULL} ;
//char *const  arvg2_multi[] = {"Multi", "Sustituido", "Multiplicar", NULL} ;
//char *const  arvg2_div[]   = {"Division", "Sustituido", "Dividir", NULL} ;
float operandos[2];

//variables memoria compartida
key_t Clave;
int ID;
struct Memoria *ptr;

//variables Fork
pid_t pid;
int val ;  

int main(int argc, char *argv[]){

    char *ando;
    char *ope;
    char operador;
    
    /*Validamos que se ingrese la Operacion*/
    if( argc != 2 )
    {
        printf("Error, en los argumentos al momento de ejcutar el programa, Deben de ser 2\n.....Ejemplo-> ./nombreArchivo operacion\n");
    } 

    ope = (char*) malloc( strlen(*argv) + 1 );//Asignamos memoria a ope
    strcpy( ope,argv[1] );//copiamos el argv[1] en ope
    /*Hacemos lo mismo para la cadena ando*/
    ando = (char*) malloc( strlen(*argv) + 1 );//Aisgnamos memoria a ope
    strcpy( ando, argv[1]);//copiamos el argv[1] en ope

/*VALIDAR Y OBTENER OPERADOR*/

        /* 
            char verificaoperadOperador(char *);
            
            *Con esta funcion obtenemos el operador
            Return
            *Esta funcion retorna  el operador, solo en caso de encontrarlo
            *O en caso contrario, regresa la letra 'e', que significara Error, y operador invalido
        */
        operador = verificaOperador(ope);

        if( operador != 'e')//evaluamos lo que devuelve la funcion
        {
            /*
                void obtenOperando(char *);
                *Con este metodo obtenemos, los operandos
                    los cuales se guardan en un array de tamanio 2
                    De tipo float
                    Se llama float reales[2]
                    Y esta declarado como global
            */
            obtenOperandos(ope);
            printf("SE IMPRIMEN VALORES DE OPERANDOS\n %f, %f\n", operandos[0], operandos[1]);
              
             

//......INICO PARA CREAR MEMORIA COMPARTIDA
            crearMemoriCompartida();
//............COMENSAMOS CON FORK
            sleep(5);
            creaProcesoHijo(operador);
            sleep(15);

//.....EN ESTE MOMENTO HACEMOS LA SUSTITUCION Y PASAMOS CLAVE DE MEMORIA COMPARTIDA

            //printf("soy el %d,mi pid es %d  y  mi val= %d\n",getpid(), pid, val);  
            sustituyeProceso(operador);

/*
            while( ptr->estado != RECIBIDO);
            sleep(5);  

            printf("calcu: El resultado es %f\n",ptr->resultado);    
    
//..... AQUI SE LIBERA MEMORIA.H
            printf("calcu: Se a entregado la informacion...\n");
            shmdt( (void *)ptr );
            shmctl( ID, IPC_RMID, NULL);
            printf("calcu: Liberando memoria compartida\n");
            printf("calcu: Terminado\n");
*/














///duplicaProceso( operador );
    // muestraResultado(operador);
//printf("Mi pid vale %d,  Soy el proceso %d, mi padre es el %d y mi val %d\n",pid,  getpid(), getppid(), val);
            
            
            

            
        }//fin if operador

        sleep(10);
        //while(1);
        free(ope);
        free(ando);
    return 0; 
}//fin main


void sustituyeProceso(char operador)
{
    if( val == 10 && pid == 0 )
    {
        switch( operador )
        {
            case '+':
                execv("./suma", datos_clave);    
                while( ptr->estado != RECIBIDO);
                printf("calcu: El resultado es %f\n",ptr->resultado);
            break;

            case '-':
                execv("./resta", datos_clave);    
            break;

            case 'x':
                execv("./multi", datos_clave);    
            break;

            case '/':
                execv("./div", datos_clave);    
            break;
        } //fin switch operador  
    }//fin if val = 10....
    
    if( val < 10 && val > 0 && pid == 0)
    {   
        sleep(5);
        switch( val )
        {
            case 1:
               // printf("Soy el %d mi val = %d mi pid es %d\n", getpid(), val, pid);
                execv("./suma", datos_clave);
                while( ptr->estado != RECIBIDO);
                printf("calcu: El resultado es %f\n",ptr->resultado);    
            break;

            case 2:
                printf("\n");
                //printf("Soy el %d mi val = %d mi pid es %d\n", getpid(), val, pid);
                /*execv("./resta", datos_clave);    
                while( ptr->estado != RECIBIDO);
                printf("calcu: El resultado es %f\n",ptr->resultado);*/
            break;

            case 3:
                printf("\n");
               // printf("Soy el %d mi val = %d mi pid es %d\n", getpid(), val, pid);
                /*execv("./multi", datos_clave);    
                while( ptr->estado != RECIBIDO);
                printf("calcu: El resultado es %f\n",ptr->resultado);*/
            break;

            case 4:
                printf("\n");
                //printf("Soy el %d mi val = %d mi pid es %d\n", getpid(), val, pid);
                /*execv("./div", datos_clave);    
                while( ptr->estado != RECIBIDO);
                printf("calcu: El resultado es %f\n",ptr->resultado);*/
            break;
        }//fin switch
        
    }//fin if val == 1,  val ==2 .....,    
}// fin sustituyeProceso

void creaProcesoHijo(char operador)
{
    val = 0;
    printf("\ncalcu: CREANDO PROCESO O PROCESOS HIJO\n");
    if( operador == '+' || operador == '-' || operador == 'x' || operador == '/')
    {
        pid = fork();   
        if( pid == 0)
        {
            printf("\ncalcu:PROCESO  HIJO CREADO\n");
           // printf("Soy el %d, mi padre es el %d\n", getpid(), getppid());
            val = 10;
        }//fin if pid==0
    }//fin if operadores

    if( operador == '#' )
    {
        for ( int i = 0 ; i < 4 ; i++ )
        {
            pid = fork();   
            if( pid == 0)
            {
                switch( i )
                {
                    case 0:
                        val = 1; 
                        //printf("Soy el %d mi val = %d\n", getpid(), val);
                    break;

                    case 1:
                        val = 2; 
                        //printf("Soy el %d mi val = %d\n", getpid(), val);
                    break;

                    case 2:
                        val = 3; 
                        //printf("Soy el %d mi val = %d\n", getpid(), val);
                    break;
                    
                    case 3:
                        val = 4; 
                        //printf("Soy el %d mi val = %d\n", getpid(), val);
                    break;
                }
                break;
                printf("\ncalcu:PROCESO  HIJO CREADO\n");
            }//fin if pid==0
        }// fin for para 4 fork's        
    }//fin if operador==#
}//Fin creaProcesoHijo()

void crearMemoriCompartida()
{
     printf("Calcu: Id es %d\n", (int) getpid());
            Clave = ftok(".", 'd');
            ID    = shmget(Clave, sizeof(struct Memoria), IPC_CREAT | 0666);

            if( ID < 0 )
            {
                printf("***ERROR!!, en shmget (Calcu ***\n)");
                exit(1);
            }
            printf("Calcu: Se utilizara memoria compartida, para almacenar 4 valores enteros\n");

            ptr = (struct Memoria *) shmat( ID, NULL, 0 );//El permiso es 
            if( ((int) ptr ) == -1 )
            {
                printf("***Calcu: ERROR!!, en shmat***\n");
                exit(1);
            }
            printf("Calcu: Usando la memoria compartida...\n");

            ptr->estado   = NOLISTO;
            ptr->operando_1 = operandos[0];
            ptr->operando_2 = operandos[1] ;

            printf("Calcu: Los datos colocados en la memoria compartida son %f, %f\n", ptr->operando_1, ptr->operando_2);
            ptr->estado = LLENO;

            
}// fin creaMemoriaCompartida()

void muestraResultado(char operador)
{
    switch( operador )
    {
        case '+':
            printf("Resultado: %f\n", ptr->resultado);
        break;
        case '-':
            printf("Resultado: %f\n", ptr->resultado);
        break;
        case 'x':
            printf("Resultado: %f\n", ptr->resultado);
        break;
        

    }

}//fin muestraResultado

/*
void duplicaProceso(char operador)
{    
    sleep(5);
    switch( operador )
    {   
        case '+':
                pid = fork();
                if( pid == 0 )
                {
                    printf("Nuevo proceso creado\n");
                    sleep(5);
                    printf("Se esta generando un espacio de memoria compartida para llamar a funcion experta\n\n");


                    Clave = ftok("." , 'd');
                    ID = shmget( Clave, sizeof(struct Memoria), IPC_CREAT | 0666 ); 
                    if( ID < 0)
                    {
                        printf("***ERROR!!, en shmget (Proceso 1***\n)");
                        exit(1);
                    }

                    ptr = (struct Memoria *) shmat( ID, NULL, 0 );//El permiso es 
                    if( ((int) ptr) == -1 )
                    {
                        printf("***Proceso 1: ERROR!!, en shmat***\n");
                        exit(1);
                    }
                    printf("Calcu: Usando la memoria compartida...\n"); 
                    printf("SE IMPRIMEN VALORES DE OPERANDOS\n");
                    printf("operando1 %f, operando2 %f \n ", operandos[0], operandos[1] );
                    ptr->estado = NOLISTO;
                    ptr->operando_1 = operandos[0];
                    ptr->operando_2 = operandos[1];

                    sleep(5);
                    printf("Calcu: Los datos colocados en la memoria compartida son %f, %f\n", ptr->operando_1, ptr->operando_2);

                    ptr->estado = LLENO;

                    printf("Calcu: Por favor, ejecuta al cliente en otra terminal\n");
                    sleep(5);
                    execv("./suma", datos_clave);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                    

                    
                    printf("Valor del estado %d\n", ptr->estado);
                    sleep(5);
                    while( ptr->estado != RECIBIDO);
                    
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                    printf("Calcu: Se a entregado la informacion...\n");
                    shmdt( (void *)ptr );
                    shmctl( ID, IPC_RMID, NULL);
                    printf("Calcu: Liberando memoria compartida\n");
                    printf("Calcu: Terminado\n"); 
                    printf("Resultado %f\n", ptr->resultado);   

                
                    
                    printf("Se cambio el  proceso por suma\n");

                    

                }
        break; 

        case '-':
                pid = fork();
                if( pid == 0 )
                {
                    sleep(5);
                    execv("./resta", arvg2_resta);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                    //break;
                }
        break; 

        case 'x':
                pid = fork();
                if( pid == 0 )
                {
                    sleep(5);
                    execv("./multi", arvg2_multi);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec
                    //break;
                }
        break; 

        case '/':
                pid = fork();
                if( pid == 0 )
                {
                    sleep(5);
                    execv("./division", arvg2_div);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec
                    //break;
                }
        break; 

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
                                sleep(5);                      
                                execv("./suma", datos_clave);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                                
                            break ;

                            //CASO DOND i = 1//
                            case 1:
                                sleep(5);
                                execv("./resta", arvg2_resta);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                            break ;

                            //CASO DOND i = 2//
                            case 2:
                                sleep(5);
                                execv("./multi", arvg2_multi);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec
                            break ;

                            //CASO DOND i = 3//
                            case 3:
                                sleep(5);
                                execv("./division", arvg2_div);
                                printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec
                            break ;
                        }// fin switch
                        break;
                    }//fin if pid == 0
                }// fin for para 4 fork's
        break; //Fin case operador '#'




    }//Fin case
                
}//Fin metodo Duplica

*/

/*
void convierteTipoOperando(float parte_real)
{
    int parte_entera = parte_real;
    int valor ;
    if( parte_real - parte_entera)
    {
        valor = parte_real; 
        ptr->`
    }
    else
    {
        valro = parte_entera;
    }
    
}*/

void obtenOperandos(char *ando)
{
    char aux ;
    const char delim[] = "+-x/#";
    char *token = strtok(ando, delim);
    int i = 0 ;

    while(token != NULL)
    {   
        operandos[i] = atof(token);
        token = strtok(NULL, delim);
        i++;
    }
}//Fin metodo obtenOperador


char verificaOperador(char *ope)
{
    //Declaracion de variables
    char aux = ' ' ;
    char aux2 ;
    int i = 0 ;
    //Iteramos en el apuntador donde esta nuestra cadena
    while ( i < strlen(ope) )
    {
        aux = ope[i];
        switch ( aux )
        {
            case '+':
                aux2 = '+';
                printf("operador + valido\n");
            break;
            case '-':
                aux2 = '-';
                printf("operador - valido \n");
            break;
            case 'x':
                aux2 = 'x';
                printf("operador x valido \n");
            break;
            case '/':
                aux2 = '/';
                printf("operador / valido \n");
            break;
            case '#':
                aux2 = '#';
                printf("operador # valido\n");
            break;        
        }

       i++;
    }//fin while
    
    if( aux2 != '+' &&  aux2 != '-' && aux2 != 'x' && aux2 != '/' && aux2 != '#' )
    { 
        printf("Operador No incluido en esta calculadora\n"); 
        aux2 = 'e';
    }
    
    return aux2;
}//Fin obtenOperador
 
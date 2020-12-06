#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>

#include "memoria.h"



char verificaOperador(char *ope);
/*....char verificaoperadOperador(char *);...
    *Con esta funcion obtenemos el operador
    Return
    *Esta funcion retorna  el operador, solo en caso de encontrarlo
    *O en caso contrario, regresa la letra 'e', que significara Error, y operador invalido
*/

void obtenOperandos(char *ando);
/*....void obtenOperando(char *);....
    *Con este metodo obtenemos, los operandos
    los cuales se guardan en un array de tamanio 2
    De tipo float
    Se llama float reales[2]
    Y esta declarado como global
*/

void crearMemoriCompartida();
/*....void crearMemoriCompartida();....
    *Con este metodo creamos la memoria compartida para la comunicacion del calcuPadre-calcuExperto
    aqui inicializamos la Clave, mediante ftok, a la cual
    le pasamos como parametros "." y 'd', el cual sera enviado los procesos expertos posteriormente
    utilizaamos shmget,shmat
    y le pasamos los valores de cada operador, asi como el estado en NOLISTO
*/

void creaProcesoHijo();
/*....void creaProcesoHijo();....
    *Con este metodo, creamos los procesos hijos necesarios, y en dependencia del operador ingresado
    tenemos 2 casos.
    Caso 1: Cuando el operador es para +,-,x,/. Creamos 1 solo proceso hijo.
    Caso 2: Cuando el operador es #. Creamos 4 procesos hijos. Esto se hace mediante:
        > Un for, con 4 iteraciones, dentro de las cuales, hacemos 1 llamada a fork
        > y mediante una condicion, creamos solo 4 hijos para el padre proceso "calcu"
        > despues de esa creacion, asignamos un valor distinto, para identificar cada proceso hijo.
*/

void sustituyeProceso();
/*....
void sustituyeProceso();....
    *Con este metodo, haceemos la sustitucion, de caad proceso, 
    pero se condiciona a 2 casos.
    Caso 1: Cuando val = 10, quiere decir que el proceso padre, tiene 1 solo hijo
        > y se susutituye 1 solo proceso
    Caso 2: Aqui adentro, hay 4 casos que se tienen que realizar por separado, pues se hacen en simultaneo
        > aqui se evalua en una structura de seleccion switch, donde:
        > val = 1 --> es igual al proceso suma
        > val = 2 --> es igual al proceso resta
        > val = 3 --> es igual al proceso multi
        > val = 4 --> es igual al proceso div
*/

void sustituye();
/*....
void sustituyeProceso();....
    *Con este metodo, solo sustituimos los procesos para el caso 1,
    donde se crea 1 solo hijo del proceso padre "calcu"
*/

void muestraResultado();
/*....
void muestraResultado();....
    *Con este metodo, mostramos los resultados que nos dio 1 o 4 procesos 
        expertos, y que dejaron en la memoria compartia
*/

//variables para expresion
float operandos[2];
char operador;

//variables memoria compartida
key_t Clave;
int ID;
struct Memoria *ptr;
char *const  datos_clave[] = {".","100", NULL};

//variables Fork
pid_t pid;
int val ;  

int main(int argc, char *argv[]){

    char *ando;
    char *ope;
        
    /*Validamos que se ingrese la Operacion*/
    if( argc != 2 )
    {
        printf("calcu: Error, en los argumentos al momento de ejcutar el programa, Deben de ser 2\n.....Ejemplo-> ./nombreArchivo operacion\n");
    } 

    ope = (char*) malloc( strlen(*argv) + 1 );//Asignamos memoria a ope
    strcpy( ope,argv[1] );//copiamos el argv[1] en ope
    /*Hacemos lo mismo para la cadena ando*/
    ando = (char*) malloc( strlen(*argv) + 1 );//Aisgnamos memoria a ope
    strcpy( ando, argv[1]);//copiamos el argv[1] en ope

    /*VALIDAR Y OBTENER OPERADOR*/
    operador = verificaOperador(ope);

    if( operador != 'e')//evaluamos lo que devuelve la funcion
    {            
            obtenOperandos(ope);
            printf("calcu: SE IMPRIMEN VALORES DE OPERANDOS\n %f, %f\n", operandos[0], operandos[1]);         
    //......INICO PARA CREAR MEMORIA COMPARTIDA
            crearMemoriCompartida();
    //............COMENSAMOS CON FORK
            sleep(5);
            creaProcesoHijo();
    //.....EN ESTE MOMENTO HACEMOS LA SUSTITUCION Y PASAMOS CLAVE DE MEMORIA COMPARTIDA
            sleep(5);   
            sustituyeProceso();
            sleep(10);
            ptr->estado = LLENO;         
                

            while( ptr->estado != RECIBIDO);
            
    //......MOSTRAMOS RESULTADOS            
            //sleep(10);    
            muestraResultado(operador);    
    //..... AQUI SE LIBERA MEMORIA.H
            printf("calcu: Se a entregado la informacion...\n");
            shmdt( (void *)ptr );
            shmctl( ID, IPC_RMID, NULL);
            printf("calcu: Liberando memoria compartida\n");
            printf("calcu: Terminado\n");     
            sleep(5);
    }//fin if operador
        free(ope);
        free(ando);
    return 0; 
}//fin main

void muestraResultado()
{
    switch(operador)
    {
        case '+':
            printf("calcu: El resultado de la suma de %.3f+%.3f = %.3f\n", ptr->operando_1, ptr->operando_2, ptr->resultado);
        break;

        case '-':
            printf("calcu: El resultado de la resta de %.3f+%.3f = %.3f\n", ptr->operando_1, ptr->operando_2, ptr->resultado);
        break;

        case 'x':
            printf("calcu: El resultado de la multiplicacion de %.3f+%.3f = %.3f\n", ptr->operando_1, ptr->operando_2, ptr->resultado);
        break;

        case '/':
            printf("calcu: El resultado de la division de %.3f+%.3f = %.3f\n", ptr->operando_1, ptr->operando_2, ptr->resultado);
        break;
    }//fin switch
}//fin muestraResultado()

void sustituye()
{
    switch( operador )
        {
            case '+':
                printf("calcu: Haciendo susutitucion por proceso suma\n");
                execv("./suma", datos_clave);    
            break;

            case '-':
                printf("calcu: Haciendo susutitucion por proceso rest\n");
                execv("./resta", datos_clave);    
            break;

            case 'x':
                printf("calcu: Haciendo susutitucion por proceso multi\n");
                execv("./multi", datos_clave);    
            break;

            case '/':
                printf("calcu: Haciendo susutitucion por proceso div\n");
                execv("./div", datos_clave);    
            break;
        } //fin switch operador  
}//fin sustituye

void sustituyeProceso()
{
    if( val == 10 && pid == 0 )
    {
        sustituye();
    }//fin if val = 10....
    
    if( val < 10 && val > 0 && pid == 0)
    {  // printf("sleep ates sqitch\n");
        sleep(5);
        switch( val )
        {
            case 1:
               // printf("Soy el %d mi val = %d mi pid es %d\n", getpid(), val, pid);
                //printf("calcu: CASO 1, esperamos (5s)\n");
                //printf("sleep ates execv(suma)\n");
                sleep(5);
                execv("./suma", datos_clave);
                //printf("\n");  
            break;

            case 2:
                
                //printf("entra caso 2\n");
                //printf("calcu: CASO 2, esperamos (5s)\n");
                //printf("sleep ates execv(resta)\n");
                sleep(5);
                execv("./resta", datos_clave);
            break;

            case 3:
                //printf("calcu: CASO 3, esperamos (5s)\n");
                sleep(5);
                execv("./multi", datos_clave);
            break;

            case 4:
                //printf("calcu: CASO 4, esperamos (5s)\n");
                sleep(5);
                execv("./div", datos_clave);
            break;
        }//fin switch
    }//fin if val == 1,  val ==2 .....,    
}// fin sustituyeProceso

void creaProcesoHijo()
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
        printf("Calcu: Se utilizara memoria compartida\n");

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
        // ptr->estado = LLENO;            
}// fin creaMemoriaCompartida()

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
 
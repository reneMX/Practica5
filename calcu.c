#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>





char verificaOperador(char *ope);
void obtenOperandos(char *ando, char *operandos);
void duplicaSustituyeProceso(char operador);

char *const  arvg2_suma[] = {"suma", "Sustituido", "Sumar", NULL} ;
char *const  arvg2_resta[] = {"resta", "Sustituido", "Restar", NULL} ;
char *const  arvg2_multi[] = {"Multi", "Sustituido", "Multiplicar", NULL} ;
char *const  arvg2_div[] = {"Division", "Sustituido", "Dividir", NULL} ;


int main(int argc, char *argv[]){

    char *ando;
    char *ope;
    char operador;
    char *operandos;
    // char *delim = "[0|1|2|3|4|5|6|7|8|9][.][0|1|2|3|4|5|6|7|8|9]";
    // char *delim1 = "+-*/#";

    
    
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

        operandos = (char*) malloc(strlen(*argv) + 1);

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
            */
            obtenOperandos(ope, operandos);
             
             /*
                void duplicaSustituyeProceso(char );
                *Con este metodo duplicaremos el proceso las veces que el operador lo indique
                *Ademas, realizaremos la sustitucion del proceso, 
                    *justo cuando estemos en el operador seleccionado.
            */
            duplicaSustituyeProceso( operador );

            

            
        }//fin if operador

            while(1);
        free(ope);
        free(ando);
    return 0; 
}


void duplicaSustituyeProceso(char operador)
{
    pid_t pid;
    
        switch ( operador )
        {
            //CASO +//
            case '+':
                pid = fork();
                if( pid == 0 )
                {
                    //printf("Soy el proceso  hijo %d\n", getpid());                
                    sleep(5);
                    execv("./suma", arvg2_suma);
                    printf("Error\n");//Solo en caso de que no se haga el cambio de proceso con exec 
                }
                while(1);
                //printf("Para clonar + \n");
            break;

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
        }

}//Fin metodo Duplica



void obtenOperandos(char *ando, char *operandos)
{
    char aux ;
    const char delim[] = "+-*/#";
    char *token = strtok(ando, delim);
    int i = 0 ;

    while(token != NULL)
    {   
        aux = token[i];
        strcat(operandos, " ");//agrego un espacio, para que no se junten los operandos
        strcat(operandos, token);
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
 



 /*
 pid_t pid;
            if( operador == '+' )
            {
                pid = fork();
                    if( pid == 0 )
                    {
                        printf("Soy el proceso  hijo %d\n", getpid());    
                        printf("%s : %d \n ",argv[0] , getpid());  
                        
                        char *const arvg2[] = {"suma", "sustituido", "Sumar", NULL} ;
                        sleep(5);
                        execv("./suma", arvg2);

                        printf("Error\n"); 
                        
                    }
            }//fin if
 
 
 */
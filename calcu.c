#include <stdio.h>
#include <string.h>
#include <stdlib.h>




char obtenOperador(char *ope);
void obtenOperandos(char *ando, char *operandos);
// char obtenOperando(char *ope);


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

/*OBTENER OPERADOR Y OPERANDO*/
        /*
            *Con esta funcion obtenemos el operador
            *El cual,se guarda en 
        */

        operador = obtenOperador(ope);
        printf("Operador dentro del main %c \n", operador);

        switch ( operador )
        {
            case '+':
                // pid_s = fork();
                printf("Operador %c \n", operador);
            break; 

            case '-' :
                // pid_s = fork();
                printf("Operador %c \n", operador);
            break; 

            case '*' :
                // pid_s = fork();
                printf("Operador %c \n", operador);
            break; 

            case '/' :
                // pid_s = fork();
                printf("Operador %c \n", operador);
            break; 

            case '#' :
                 // pid_s = fork();
                printf("Operador %c \n", operador);
            break; 
        }  

        obtenOperandos(ope, operandos);
         

         free(ope);
         free(ando);
    return 0; 
}




void obtenOperandos(char *ando, char *operandos)
{
    char aux ;
    const char delim[] = "+-*/#";
    // const char delim1[] ="[0|1|2|3|4|5|6|7|8|9][.][0|1|2|3|4|5|6|7|8|9]";
    char *token = strtok(ando, delim);
    
    int i = 0 ;
    while(token != NULL)
    {   
        aux = token[i];
        strcat(operandos, " ");
        strcat(operandos, token);
        // printf("Dentro de la funcion token %s\n",token);
        token = strtok(NULL, delim);
        i++;
    }
}//Fin obtenOperador




















char obtenOperador(char *ope)
{
    char aux ;
    //  const char delim1[] = "+-*/#";
    const char delim1[] ="[0|1|2|3|4|5|6|7|8|9][.][0|1|2|3|4|5|6|7|8|9]";
    char *token = strtok(ope, delim1);
    int i = 0 ;
    while(token != NULL)
    {   
        aux = token[i];
        printf("Dentro de la funcion token %s\n",token);
        token = strtok(NULL, delim1);
        i++;
    }
    return aux; 
    
}//Fin obtenOperador
#define NOLISTO -1
#define LLENO 0
#define RECIBIDO 1

struct Memoria{
    int estado;
    float operando_1;
    float operando_2;
    float resultado;
    char *mensaje_error;
};
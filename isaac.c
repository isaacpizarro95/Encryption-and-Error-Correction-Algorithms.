// Arxiu gestió programa
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int main(int argc, char *argv[]){
    int p = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m[p-1][k];

    /* 1. Creant matriu */
    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    /* 2. Aplicant la reducció Gaussiana */
    reduccio_gaussiana(p, p-1, k, m);
    /* 3. Discussió del sistema */
    discussio_sistemes(p, p-1, k, m);
    return 0;
}
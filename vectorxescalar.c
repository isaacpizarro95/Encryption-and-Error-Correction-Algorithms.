// Multiplicació de vector per un element a de Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void vectorxescalar(int dim, int a, int p, double vector[]){
    double resul[dim];
    for(int i = 0; i < dim; i++){
        resul[i] = (int)(a * vector[i]) % p;
    }
    printf("El resultat de multiplicar el vector per %d en F(%d) és\n", a, p);
    imprimeixvector(dim, resul);
    return;
}
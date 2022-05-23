// Multiplicació de matrius quadrades i no quadrades amb coeficients de Fp.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void matriuxvector(int dim, int p, double vect[], double mat[][dim]){
    double resul[dim];
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            resul[i] += (vect[j] * mat[j][i]);
        }
        resul[i] = (int)resul[i] % p;
    }
    printf("El resultat de multiplicar el vector i matriu introduïdes és\n");
    imprimeixvector(dim, resul);
    return;
}
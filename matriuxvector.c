// Multiplicació de matrius quadrades i no quadrades amb coeficients de Fp.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void matriuxvector(int dim, int p, int vect[], int mat[][dim]){
    int resul[dim];
    for(int i = 0; i < dim; i++){
        resul[i] = 0;
        for(int j = 0; j < dim; j++){
            resul[i] += (vect[j] * mat[j][i]) % p;
        }
        resul[i] = resul[i] % p;
    }
    printf("El resultat de multiplicar el vector i matriu introduïdes és\n");
    imprimeixvector(dim, resul);
    return;
}
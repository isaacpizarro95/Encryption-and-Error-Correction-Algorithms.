// Multiplicació de matrius quadrades i no quadrades amb coeficients de Fp.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void matriuxvector(int dim, int p, int vect[], int codificat[], int mat[][dim]){
    for(int i = 0; i < dim; i++){
        codificat[i] = 0;
        for(int j = 0; j < dim; j++){
            codificat[i] += (vect[j] * mat[j][i]) % p;
        }
        codificat[i] = codificat[i] % p;
    }
    return;
}
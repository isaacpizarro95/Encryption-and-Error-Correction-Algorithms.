// Multiplicació de matrius quadrades i no quadrades amb coeficients de Fp.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void matriuxvector_codificar(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]){
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            resultat[i] += (mat[i][j] * vect[j]) % p;
        }
        resultat[i] = resultat[i] % p;
    }
    return;
}

void matriuxvector_descodificar(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]){
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            resultat[i] += (vect[j] * mat[j][i]) % p;
        }
        resultat[i] = resultat[i] % p;
    }
    return;
}
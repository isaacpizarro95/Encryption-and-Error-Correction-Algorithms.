// Codificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void descodificacio(int p, int r, int k, int codificat[r/k][p-1], int descodificat[r/k][k], int m[p-1][k], int missatge_descodificat[]){
    for(int i = 0; i < r/k; i++){
        matriuxvector_descodificar(p, p-1, k, codificat[i], descodificat[i], m);
    }

    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < p-1; j++){
            missatge_descodificat[j+l] = descodificat[i][j];
        }
        l += k;
    }
    return;
}
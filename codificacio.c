// Codificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void codificacio(int p, int r, int k, int paraula[r/k][k], int codificat[r/k][p-1], int m[p-1][k], int missatge_codificat[]){
    for(int i = 0; i < r/k; i++){
        matriuxvector(p, p-1, k, paraula[i], codificat[i], m);
    }

    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < p-1; j++){
            missatge_codificat[j+l] = codificat[i][j];
        }
        l += p-1;
    }
    return;
}
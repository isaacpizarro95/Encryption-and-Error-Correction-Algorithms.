// Codificació
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void llegeix_missatge(int p, int r, int k, int missatge[r]){
    while(r % k != 0){
        // REDIMENSIONAR EL VECTOR SUCCESSIO AMB REALLOC O ALGO AIXI PER AUMENTAR EL TAMANY DEL VECTOR I FICAR ELEMENTS
        r++;
    }
    llegeixvector(p, r, missatge);
}

void dividir_missatge(int r, int k, int missatge[r], int paraules[r/k][k]){
    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < k; j++){
            paraules[i][j] = missatge[j+l];
        }
        l += k;
    }
    return;
}

void codificacio(int p, int k, int paraula[k], int codificat[k], int m[p-1][k]){
    matriuxvector(k, p, paraula, codificat, m);
    return;
}
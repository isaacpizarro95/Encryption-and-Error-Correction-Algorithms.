// Codificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void descodificacio(int p, int r, int k, int codificat[r/k][p-1], int descodificat[r/k][k], int m[p-1][k], int missatge_descodificat[]){
    // Apliquem la reducció Gaussiana
    for(int i = 0; i < r/k; i++){
        // k+1 a les columnes per afegir la columna b de la matriu ampliada
        reduccio_gaussiana(p, p-1, k+1, codificat[i], descodificat[i], m);
        printf("\n");
    }

    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < k; j++){
            missatge_descodificat[j+l] = descodificat[i][j];
        }
        l += k;
    }
    return;
}
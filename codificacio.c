// Codificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void codificacio(int p, int k, int paraula[k], int codificat[k], int m[p-1][k]){
    matriuxvector(k, p, paraula, codificat, m);
    return;
}
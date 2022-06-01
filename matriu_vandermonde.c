// Funcions per crear la matriu de codificació
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]){
    int a_primitiu = element_primitiu(p);
    for(int i = 0; i < files; i++) {
        for(int j = 0; j < cols; j++) {
            m[i][j] = calcul_potencia(p, a_primitiu, i*j);;
        }
    }
    return;
}
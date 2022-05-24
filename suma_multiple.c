// Suma a una fila d'una matriu un múltiple d'una altra sobre Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void suma_multiple(int multiple, int p, int fila_inici, int fila_desti, int cols, int m[][cols]){
    int aux_vector[cols];

    for(int j = 0; j < cols; j++){
        aux_vector[j] = multiple * m[fila_inici][j];
        m[fila_desti][j] = (m[fila_desti][j] + aux_vector[j]) % p;
    }
    return;
}
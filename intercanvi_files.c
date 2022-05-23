// Intercanvia dues files d'una matriu
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void intercanvi_files(int fila_inici, int fila_desti, int cols, double m[][cols]){
    double aux_vector[cols];

    for(int j = 0; j < cols; j++){
        aux_vector[j] = m[fila_desti][j];
        m[fila_desti][j] = m[fila_inici][j];
        m[fila_inici][j] = aux_vector[j];
    }
    return;
}
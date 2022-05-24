// Multiplicació de vector per un element a de Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Multiplica un vector qualsevol per un element de Fp
void vectorxescalar(int dim, int a, int p, int vector[]){
    int resul[dim];
    for(int i = 0; i < dim; i++){
        resul[i] = (a * vector[i]) % p;
    }
    return;
}

// Multiplica una fila d'una matriu per un element de Fp
void filaxescalar(int a, int p, int fila, int cols, int m[][cols]){
    for(int i = 0; i < cols; i++){
        m[fila][i] = (a * m[fila][i]) % p;
    }
    return;
}
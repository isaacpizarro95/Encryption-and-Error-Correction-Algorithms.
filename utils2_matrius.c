// Funcions auxiliars per a vectors i matrius.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Multiplica un vector qualsevol per un element de Fp
void vectorxescalar(int dim, int a, int p, int vector[], int resul[]){
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

// Multiplica un vector por una matriu en Fp
void matriuxvector(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]){
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            resultat[i] += (mat[i][j] * vect[j]) % p;
        }
        resultat[i] = resultat[i] % p;
    }
    return;
}

// Suma a una fila d'una matriu un múltiple d'un altra en Fp
void suma_multiple(int multiple, int p, int fila_inici, int fila_desti, int cols, int m[][cols]){
    int aux_vector[cols];

    for(int j = 0; j < cols; j++){
        aux_vector[j] = multiple * m[fila_inici][j];
        m[fila_desti][j] = (m[fila_desti][j] + aux_vector[j]) % p;
    }
    return;
}

// Intercanvia dues files d'una matriu
void intercanvi_files(int fila_inici, int fila_desti, int cols, int m[][cols]){
    int aux_vector[cols];

    for(int j = 0; j < cols; j++){
        aux_vector[j] = m[fila_desti][j];
        m[fila_desti][j] = m[fila_inici][j];
        m[fila_inici][j] = aux_vector[j];
    }
    return;
}

// Calcula (a^potencia) % mòdul p
int calcul_potencia(int p, int a, int potencia){
    int a_final = a;
    if(potencia == 0){
        return 1;
    }
    for(int i = 1; i < potencia; i++){
        a_final = (a_final * a) % p;
    }
    a_final = a_final % p;
    return a_final;
}

// Crea la matriu de codificació
void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]){
    int a_primitiu = element_primitiu(p);
    for(int i = 0; i < files; i++) {
        for(int j = 0; j < cols; j++) {
            m[i][j] = calcul_potencia(p, a_primitiu, i*j);;
        }
    }
    return;
}
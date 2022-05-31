// Funcions per llegir i imprimir vectors i matrius de qualsevol dimensió.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Retorna 1 si el vector és nul, és a dir vect = {0, 0, ... , 0} i 0 si no ho és
int vector_nul(int dim, int vect[]){
    for(int i = 0; i < dim; i++){
        if(vect[i] != 0){
            return 0;
        }
    }
    return 1;
}

// Comprova si un vector fa que la matriu sigui incompatible. Retorna 1 si és incompatible i 0 si és compatible
int vector_incompatible(int dim, int vect[]){
    int compatible = 0;
    if(vect[dim-1] == 0){
        return 0;
    }
    for(int i = 0; i < dim-1; i++){
        if(vect[i] != 0){
            compatible = 1;
        }
    }
    if(compatible == 0){
        return 1;
    }
    return 0;
}

void llegeixvector(int p, int dim, int vect[]){
    for(int i = 0; i < dim; i++){
        printf("v(%d) = ", i + 1);
        scanf("%d", &vect[i]);
        vect[i] = vect[i] % p;
    }
    return;
}

// Cada valor que es llegeix de la matriu s'ha de reduir mòdul p
void llegeixmatriu(int p, int files, int cols, int m[][cols]){
    for(int i = 0; i < files; i++) {
        for(int j = 0; j < cols; j++) {
            printf("a(%d, %d) = ", i+1, j+1);
            scanf("%d", &m[i][j]);
            m[i][j] = m[i][j] % p;
        }
    }
    return;
}

void imprimeixvector(int dim, int vect[]){
    for(int i = 0; i < dim; i++){
        printf("%d\t", vect[i]);
    }
    printf("\n\n");
    return;
}

void imprimeixmatriu(int files, int cols, int m[][cols]){
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
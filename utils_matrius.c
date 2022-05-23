// Funcions per llegir i imprimir vectors i matrius de qualsevol dimensió.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Retorna 1 si el vector és nul, és a dir vect = {0, 0, ... , 0} i 0 si no ho és
int vector_nul(int dim, double vect[]){
    for(int i = 0; i < dim; i++){
        if(vect[i] != 0){
            return 0;
        }
    }
    return 1;
}

// Comprova si un vector fa que la matriu sigui incompatible. Retorna 1 si és incompatible i 0 si és compatible
int vector_incompatible(int dim, double vect[]){
    int suma = 0;
    
    for(int i = 0; i < dim-1; i++){
        suma += vect[i];
    }
    if(suma == 0 && vect[dim] != 0){
        return 1;
    }
    return 0;
}

void llegeixvector(int dim, double vect[]){
    for(int i = 0; i < dim; i++){
        printf("v(%d) = ", i + 1);
        scanf("%lf", &(vect[i]));
    }
    return;
}

// Cada valor que es llegeix de la matriu s'ha de reduir mòdul p
void llegeixmatriu(int files, int cols, double m[][cols]){
   int i, j;
   for(i = 0; i < files; i++) {
      for(j = 0; j < cols; j++) {
         printf("a(%d, %d) = ", i+1, j+1);
         scanf("%lf", &m[i][j]);
      }
   }
   return;
}

void imprimeixvector(int dim, double vect[]){
    for(int i = 0; i < dim; i++){
        printf("%lf    ", vect[i]);
    }
    printf("\n");
    return;
}

void imprimeixmatriu(int files, int cols, double m[][cols]){
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            printf("%lf    ", m[i][j]);
        }
        printf("\n");
    }
    return;
}
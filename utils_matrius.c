// Funcions per llegir i imprimir vectors i matrius de qualsevol dimensió.
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

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

void llegeixvector(int p, int dim, int vect[]){
    for(int i = 0; i < dim; i++){
        printf("v(%d) = ", i + 1);
        scanf("%d", &vect[i]);
        vect[i] = vect[i] % p;
    }
    return;
}

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
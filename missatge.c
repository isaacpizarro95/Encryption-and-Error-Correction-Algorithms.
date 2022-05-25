// Processament del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Comprova si r és divisible per k i si no ho és, redimensiona amb realloc el vector 'missatge' amb un r on r % k = 0
int realloc_missatge(int r, int k, int *missatge){
    //int aux = r;
    int *nou_missatge;

    while(r % k != 0){
        r++;
    }

    if((nou_missatge = (int *) realloc (missatge, r * sizeof(int))) == NULL){
        printf("[ERROR] Realloc no ha pogut redimensionar l'espai de memòria\n");
        exit(1);        
    };
    missatge = nou_missatge;
    printf("Imprimir missatge in realloc\n");
    imprimeixvector(r, missatge);
    return r;
}

void dividir_missatge(int r, int k, int missatge[r], int paraules[r/k][k]){
    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < k; j++){
            paraules[i][j] = missatge[j+l];
        }
        l += k;
    }
    return;
}
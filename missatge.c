// Processament del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Redimensionem el tamany del missatge en cas de que la seva longitud no sigui divisible per k
int *realloc_missatge(int aux_r, int r, int k, int *missatge){
    int *nou_missatge;
    
    if((nou_missatge = (int *) realloc (missatge, r * sizeof(int))) == NULL){
        printf("[ERROR] Realloc no ha pogut redimensionar l'espai de memòria\n");
        exit(1);        
    };

    for(int i = aux_r; i < r; i++){
        nou_missatge[i] = 0; 
    }

    missatge = nou_missatge;
    return missatge;
}

// Divideix el missatge en paraules(vectors) formant una matriu de paraules
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
// Codificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void codificar(int p, int k, FILE *fitxer, int m[p-1][k]){
    // 2. Llegim missatge
    // Llegirlo del fitxer
    int r = (k*3)+1; // Llargada del missatge
    int *missatge;
    if((missatge = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    for(int i = 0; i < r; i++){
        missatge[i] = (i*i) % p; // Missatge arbitrari per fer proves
    }

    // Si r no és múltiple de k
    if(r % k != 0){
        int aux_r = r;
        r = (r + k) - (r % k);
        missatge = realloc_missatge(aux_r, r, k, missatge);
    }
    printf("\nMissatge\n");
    imprimeixvector(r, missatge);


    // 3. Dividim el missatge en paraules
    printf("\nDividim el missatge en paraules\n\n");

    int (*paraules)[k];
    if((paraules = (int (*)[k]) malloc((r/k) * k * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    };
    dividir_missatge(r, k, missatge, paraules);
    imprimeixmatriu(r/k, k, paraules);
    printf("\n");


    // 4. Codifiquem el missatge
    printf("\nCodifiquem el missatge\n\n");
    int (*codificat)[p-1];
    if((codificat = (int (*)[p-1]) malloc((r/k) * (p-1) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }
    int *missatge_codificat;
    if((missatge_codificat = (int *) malloc(((r/k)*(p-1)) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    codificacio(p, r, k, paraules, codificat, m, missatge_codificat);
    imprimeixmatriu(r/k, p-1, codificat);
    printf("\nMissatge codificat\n");
    imprimeixvector(((r/k)*(p-1)), missatge_codificat);
    printf("\n");

    free(missatge);
    free(paraules);
    free(missatge_codificat);
    free(codificat);
    free(m);
}

void codificacio(int p, int r, int k, int paraula[r/k][k], int codificat[r/k][p-1], int m[p-1][k], int missatge_codificat[]){
    for(int i = 0; i < r/k; i++){
        matriuxvector(p, p-1, k, paraula[i], codificat[i], m);
    }

    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < p-1; j++){
            missatge_codificat[j+l] = codificat[i][j];
        }
        l += p-1;
    }
    return;
}
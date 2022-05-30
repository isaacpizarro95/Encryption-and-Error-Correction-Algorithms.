// Descodificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void descodificar(int p, int k, char *nom_fitxer){
    // Declarem la matriu de Vandermonde
    int (*m)[k];
    if((m = (int (*)[k]) malloc((p-1) * k * sizeof(int))) == NULL){
        printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
        exit(1);
    };
    printf("\nCreem la matriu\n\n");
    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    
    // Llegim missatge
    // Comprovar el tipus de fitxer: .dat, .bin, .txt amb una funció
    FILE *fitxer;
    if((fitxer = fopen(nom_fitxer, "r")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no existeix o no es pot obrir...\n\n", nom_fitxer);
        exit(1);        
    }

    int r = len_missatge(fitxer); // Llargada del missatge
    int *missatge_codificat;
    if((missatge_codificat = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    llegeix_missatge(fitxer, missatge_codificat, p);
    printf("\nMissatge codificat\n");
    imprimeixvector(r, missatge_codificat);
    printf("\n");

    // Si r no és múltiple de n = p-1
    if(r % (p-1) != 0){
        int aux_r = r;
        r = (r + (p-1)) - (r % (p-1));
        missatge_codificat = realloc_missatge(aux_r, r, missatge_codificat);
        printf("\n\nMissatge redimensionat per a que 'r' sigui múltiple de 'p-1'\n\n");
        imprimeixvector(r, missatge_codificat);
    }

    int (*codificat)[p-1];
    if((codificat = (int (*)[p-1]) malloc((r/(p-1)) * (p-1) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }

    // 5. Descodifiquem el missatge
    printf("\nDescodifiquem el missatge\n\n");
    int (*descodificat)[k];
    if((descodificat = (int (*)[k]) malloc((r/k) * k * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }
    int *missatge_descodificat;
    if((missatge_descodificat = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }

    dividir_missatge(r/(p-1), p-1, missatge_codificat, codificat);
    printf("\nMatriu codificada\n");
    imprimeixmatriu(r/(p-1), p-1, codificat);
    printf("\n");
    descodificacio(p, r, k, codificat, descodificat, m, missatge_descodificat);
    printf("\nMissatge descodificat\n");
    imprimeixvector(r, missatge_descodificat);
    printf("\n");

    // Alliberem la memòria que haviem reservat
    free(missatge_codificat);
    free(codificat);
    free(missatge_descodificat);
    free(descodificat);
    free(m);
}

void descodificacio(int p, int r, int k, int codificat[r/k][p-1], int descodificat[r/k][k], int m[p-1][k], int missatge_descodificat[]){
    // Apliquem la reducció Gaussiana
    for(int i = 0; i < r/k; i++){
        // k+1 a les columnes per afegir la columna b de la matriu ampliada
        reduccio_gaussiana(p, p-1, k+1, codificat[i], descodificat[i], m);
        printf("\n");
    }

    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < k; j++){
            missatge_descodificat[j+l] = descodificat[i][j];
        }
        l += k;
    }
    return;
}

void descodificacio_erros(int p, int k, int errors, int v_erroni[]){
    if (errors > ((p-1) - k)){
        printf("[ERROR] Massa errors, no es poden corregir");
        exit(1);
    }
    //int errors_maxims = ((p-1)-k)/2;

    return;
}
// Codificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void codificar(int p, int k, char *nom_fitxer){
    // Declarem la matriu de Vandermonde
    int (*m)[k];
    if((m = (int (*)[k]) malloc((p-1) * k * sizeof(int))) == NULL){
        printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
        exit(1);
    };
    printf("\nCreem la matriu de codificació\n\n");
    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    
    // Llegim missatge
    FILE *fitxer;
    int r; // Longitud missatge
    int *apuntador_r = &r;
    fitxer = gestio_fitxer(nom_fitxer, apuntador_r);

    // Guardem el missatge
    int *missatge; 
    if((missatge = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    printf("\n\nMissatge\n\n");
    gestio_flectura(nom_fitxer, fitxer, missatge, p);
    imprimeixvector(r, missatge);
    
    // Si r no és múltiple de k
    if(r % k != 0){
        int aux_r = r;
        r = (r + k) - (r % k);
        missatge = realloc_missatge(aux_r, r, missatge);
        printf("\n\nMissatge redimensionat per a que 'r' sigui múltiple de 'k'\n\n");
        imprimeixvector(r, missatge);
    }

    // Dividim en vectors el missatge guardant-lo com a matriu
    printf("\n\nDividim el missatge en vectors\n\n");

    int (*paraules)[k];
    if((paraules = (int (*)[k]) malloc((r/k) * k * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    };
    dividir_missatge(r/k, k, missatge, paraules);
    imprimeixmatriu(r/k, k, paraules);
    printf("\n");

    // Codifiquem el missatge
    printf("\n\nCodifiquem el missatge\n\n");
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
    printf("\n\nMissatge codificat\n\n");
    imprimeixvector(((r/k)*(p-1)), missatge_codificat);
    printf("\n");

    // Escrivim el missatge codificat en un nou fitxer
    gestio_fescriptura(nom_fitxer, missatge_codificat, (r/k)*(p-1), "RS.");
    
    fclose(fitxer);
    free(paraules);
    free(missatge_codificat);
    free(codificat);
    free(missatge);
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
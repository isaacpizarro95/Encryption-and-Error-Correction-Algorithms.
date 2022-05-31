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
    printf("\nCreem la matriu de codificació\n\n");
    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    
    // Llegim missatge
    // Comprovar el tipus de fitxer: .dat, .bin, .txt amb una funció
    FILE *fitxer;
    if((fitxer = fopen(nom_fitxer, "r")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no existeix o no es pot obrir...\n\n", nom_fitxer);
        exit(1);        
    }

    // Guardem el missatge codificat
    int r = len_missatge(fitxer); // Llargada del missatge
    int *missatge_codificat;
    if((missatge_codificat = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    printf("\nMissatge codificat\n");
    llegeix_missatge(fitxer, missatge_codificat, p);
    imprimeixvector(r, missatge_codificat);

    int (*codificat)[p-1];
    if((codificat = (int (*)[p-1]) malloc((r/(p-1)) * (p-1) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }

    // Dividim en vectors el missatge codificat guardant-lo com a matriu
    dividir_missatge(r/(p-1), p-1, missatge_codificat, codificat);
    printf("\nMatriu codificada\n");
    imprimeixmatriu(r/(p-1), p-1, codificat);
    printf("\n");

    // Creem la matriu i el missatge de descodificació
    int (*descodificat)[k];
    if((descodificat = (int (*)[k]) malloc((r/(p-1)) * k * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }
    int *missatge_descodificat;
    if((missatge_descodificat = (int *) malloc(((r/(p-1)) * k) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }

    // A partir de la matriu codificada i la matriu de codificació trobem el missatge codificat
    printf("\nDescodifiquem el missatge\n\n");
    descodificacio(p, r/(p-1), k, codificat, descodificat, m, missatge_descodificat);
    printf("\nMatriu descodificada\n");
    imprimeixmatriu((r/(p-1)), k, descodificat);
    printf("\nMissatge descodificat\n");
    imprimeixvector(((r/(p-1))*k), missatge_descodificat);
    printf("\n");

    // Escrivim el missatge descodificat en un nou fitxer
    escriure_missatge(nom_fitxer, missatge_descodificat, (r/(p-1))*k, "BW.");

    // Alliberem la memòria que haviem reservat
    fclose(fitxer);
    free(missatge_codificat);
    free(codificat);
    free(missatge_descodificat);
    free(descodificat);
    free(m);
}

void descodificacio(int p, int files, int cols, int codificat[files][p-1], int descodificat[files][cols], int m[p-1][cols], int missatge_descodificat[]){
    // Apliquem la reducció Gaussiana
    for(int i = 0; i < files; i++){
        // cols+1 per afegir la columna b de la matriu ampliada
        reduccio_gaussiana(p, p-1, cols+1, codificat[i], descodificat[i], m);
        printf("\n");
    }

    int l = 0;
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            missatge_descodificat[j+l] = descodificat[i][j];
        }
        l += cols;
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
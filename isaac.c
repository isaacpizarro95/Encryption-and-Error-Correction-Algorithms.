// Arxiu gestió programa
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int main(int argc, char *argv[]){
    // Valors per defecte de p i k
    int p = 5; 
    int k = 3;

    // Modifiquem, si és necessari, els valors de p i k a partir dels arguments del main 
    /*if(argv[1][0] == '-' || argv[2][0] == '-'){
        int *apuntador_p = &p;
        int *apuntador_k = &k;
        check_valors(argv, apuntador_p, apuntador_k);
    }
    else {
        argv[2] será el fitxer amb el missatge a codificar
        Llegirem argv[2] i ho guardarem en el vector 'missatge[r]'
        Es dividirà en q = r/k paraules de longitud k 'paraules[q][k]'
        Es codifiquen les paraules multiplicant 
    }
    */

    // Declarem la matriu de Vandermonde
    int (*m)[k];
    if((m = (int (*)[k]) malloc((p-1) * k * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    };


    // 1. Creant matriu
    printf("\nCreem la matriu\n\n");

    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    printf("\n");


    // 2. Llegim missatge
    //printf("\nLlegim el missatge\n\n");

    int r = k*3; // Nombre arbitrari per fer proves
    int *missatge;
    if((missatge = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    //llegeixvector(p, r, missatge);
    for(int i = 0; i < r; i++){
        missatge[i] = 1;
    }

    if(r % k != 0){
        r = realloc_missatge(r, k, missatge);
        printf("r = %d\n", r);
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

    descodificacio(p, r, k, codificat, descodificat, m, missatge_descodificat);
    printf("\nMissatge descodificat\n");
    imprimeixvector(r, missatge_descodificat);
    printf("\n");


    // Alliberem la memòria que haviem reservat
    free(missatge);
    free(paraules);
    free(missatge_codificat);
    free(codificat);
    free(m);
    return 0;
}
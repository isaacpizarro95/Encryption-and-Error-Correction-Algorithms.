// Arxiu gestió programa
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int main(int argc, char *argv[]){
    //int p = 257; Valors per defecte
    //int k = 200;
    int p = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m[p-1][k];
 

    /* 1. Creant matriu */
    printf("\nCreem la matriu\n\n");
    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    printf("\n");

    /* 2. Llegim missatge */
    printf("\nLlegim el missatge\n\n");
    int r = 15;
    int missatge[r];
    llegeixvector(p, r, missatge);
    printf("\n");

    /* 3. Dividim el missatge en paraules */
    printf("\nDividim el missatge en paraules\n\n");
    int paraules[r/k][k];
    dividir_missatge(r, k, missatge, paraules);
    imprimeixmatriu(r/k, k, paraules);
    printf("\n");

    /* 4. Codifiquem el missatge */
    printf("\nCodifiquem el missatge\n\n");
    int codificat[r/k][k];
    for(int i = 0; i < r/k; i++){
        codificacio(p, k, paraules[i], codificat[i], m);
    }
    imprimeixmatriu(r/k, k, codificat);
    printf("\n");

    /* 5. Decodifiquem el missatge */


    /* 2. Aplicant la reducció Gaussiana */
    //reduccio_gaussiana(p, p-1, k, m);
    /* 3. Discussió del sistema */
    //discussio_sistemes(p, p-1, k, m);
    return 0;
}
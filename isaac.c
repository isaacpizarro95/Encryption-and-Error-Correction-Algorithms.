// Arxiu gestió programa
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int main(int argc, char *argv[]){
    // Valors per defecte de p i k
    int p = 7; 
    int k = p-3;
    // Si accio = 1 codificará, si val 0, descodificará
    int accio = -1;
    FILE *fitxer = NULL;

    // Modifiquem, si és necessari, els valors de p i k a partir dels arguments del main
    if(argc > 1){
        int *apuntador_p = &p;
        int *apuntador_k = &k;
        accio = arguments(argc, argv, apuntador_p, apuntador_k, fitxer);
    }

    // Declarem la matriu de Vandermonde
    int (*m)[k];
    if((m = (int (*)[k]) malloc((p-1) * k * sizeof(int))) == NULL){
        printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
        exit(1);
    };
    printf("\nCreem la matriu\n\n");
    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    printf("\n");

    if(accio == 1) codificar(p, k, fitxer, m);
    else if(accio ==0) descodificar();

    return 0;
}
// Descodificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void descodificar(){
    printf("\nDescodificant...\n\n");
    return;
    // 5. Descodifiquem el missatge
    /*printf("\nDescodifiquem el missatge\n\n");
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

    // Comprovem que el missatge introduit inicialment i el descodificat siguin el mateix
    char * print_missatge = NULL;
    for(int i = 0; i < r; i++){
        if(missatge[i] != missatge_descodificat[i]){
            print_missatge = "\n\nEl missatge NO coincideix\n\n";
        }
    }
    if (print_missatge == NULL){
        print_missatge = "\n\nMissatge OK\n\n";
    }
    printf("%s", print_missatge);
    printf("\tp = %d\n\n", p);

    // Alliberem la memòria que haviem reservat
    free(missatge_descodificat);
    free(descodificat);*/
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
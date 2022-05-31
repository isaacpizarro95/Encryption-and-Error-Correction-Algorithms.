// Processament de la lectura del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Retorna la longitud del missatge a llegir
int len_missatge(FILE *fitxer){
    int len = 0;
    int aux = 0;
    while (!feof(fitxer)){
        fscanf(fitxer, "%d", &aux);
        len++;
    }
    rewind(fitxer); // Ens coloquem de nou al principi del fitxer
    return len;
}

// Llegeix el contingut del fitxer guardant-lo al vector missatge
void llegeix_missatge(FILE *fitxer, int *missatge, int p){
    int i = 0;
    // Guardem els valors en 'missatge'
    while (!feof(fitxer)){
        fscanf(fitxer, "%d", &(missatge[i]));
        if(missatge[i] >= p){
            fprintf(stderr, "\n[Warning]: El fitxer té algún valor >= p. Es reduirà mòdul p\n\n");
            missatge[i] = missatge[i] % p;
        }
        i++;
    }
    rewind(fitxer);
}

// Redimensionem el tamany del missatge en cas de que la seva longitud no sigui divisible per k
int *realloc_missatge(int aux_r, int r, int *missatge){
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
void dividir_missatge(int files, int cols, int missatge[], int paraules[files][cols]){
    int l = 0;
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            paraules[i][j] = missatge[j+l];
        }
        l += cols;
    }
    return;
}
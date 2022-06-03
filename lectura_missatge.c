// Processament de la lectura del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Llegeix el missatge d'un fitxer bin
void lectura_bin(FILE *fitxer, int *missatge, int p){
    int i = 0;
    int warning = 0;
    while((fread(&missatge[i], sizeof(int), 1, fitxer)) == 1){
        if(missatge[i] >= p){
            warning = 1;
            missatge[i] = missatge[i] % p;
        }
        i++;
    }
    if(warning == 1) fprintf(stderr, "\n[Warning]: El fitxer té algún valor >= p. Es reduirà mòdul p\n\n");
}

// Llegeix el missatge d'un fitxer dat
void lectura_dat(FILE *fitxer, int *missatge, int p){
    int i = 0;
    int warning = 0;

    // Guardem els valors en 'missatge'
    while (!feof(fitxer)){
        fscanf(fitxer, "%d", &(missatge[i]));
        if(missatge[i] >= p){
            warning = 1;
            missatge[i] = missatge[i] % p;
        }
        i++;
    }
    if(warning == 1) fprintf(stderr, "\n[Warning]: El fitxer té algún valor >= p. Es reduirà mòdul p\n\n");
    rewind(fitxer);
}

// Llegeix el missatge d'un fitxer txt
void lectura_txt(FILE *fitxer, int *missatge, int p){
    char c;
    int i = 0;
    int warning = 0;
    if(p < 257){
        fprintf(stderr, "\n[ERROR] Si el fitxer és del tipus .txt p ha de ser major o igual que 257\n\n");
        exit(1);
    }
    while((c = fgetc(fitxer)) != EOF){
        missatge[i] = (int)c;
        if(missatge[i] >= p){
            warning = 1;
            missatge[i] = missatge[i] % p;
        }
        i++;
    }
    if(warning == 1) fprintf(stderr, "\n[Warning]: El fitxer té algún valor >= p. Es reduirà mòdul p\n\n");
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
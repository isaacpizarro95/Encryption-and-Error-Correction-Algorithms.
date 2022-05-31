// Processament de l'escriptura del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Llegeix el contingut del fitxer guardant-lo al vector missatge
void escriure_missatge(char *f_input, int *missatge, int len_missatge, char *afegit){
    char *f_output;
    if((f_output = (char *) malloc((strlen(f_input)+3) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    int i, j = 0;

    for(i = 0; i < strlen(f_input); i++){
        f_output[j] = f_input[i];
        if(f_input[i] == '.' && f_input[i+1] != 'R'){
            for(int k = 0; k < strlen(afegit); k++){
                j++;
                f_output[j] = afegit[k];
            }
        }
        j++;
    }
    f_output[j] = '\0';
    FILE *fitxer = fopen(f_output, "w+");
    for(int i = 0; i < len_missatge; i++){
        if(i == len_missatge-1) fprintf(fitxer, "%d", missatge[i]);
        else fprintf(fitxer, "%d ", missatge[i]);
    }
    fclose(fitxer);
}
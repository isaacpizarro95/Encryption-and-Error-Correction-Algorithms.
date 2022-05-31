// Processament de l'escriptura del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

char *nom_foutput(char *f_input, char *afegit){
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
    return f_output;
}

// Escriu el contingut del missatge en un fitxer '.dat'
void escriure_dat(char *f_input, int *missatge, int mida, char *afegit){
    char *f_output = nom_foutput(f_input, afegit);
    FILE *fitxer;
    if((fitxer = fopen(f_output, "w+")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    for(int i = 0; i < mida; i++){
        if(i == mida-1) fprintf(fitxer, "%d", missatge[i]);
        else fprintf(fitxer, "%d ", missatge[i]);
    }
    free(f_output);
    fclose(fitxer);
}

// Escriu el contingut del missatge en un fitxer '.bin'
void escriure_bin(char *f_input, int *missatge, char *afegit){
    char *f_output = nom_foutput(f_input, afegit);
    FILE *fitxer;
    if((fitxer = fopen(f_output, "w+")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    fwrite(missatge, sizeof(missatge), 1, fitxer);
    free(f_output);
    fclose(fitxer);
}

// Escriu el contingut del missatge en un fitxer '.txt'
void escriure_txt(char *f_input, int *missatge, int mida, char *afegit){
    char *f_output = nom_foutput(f_input, afegit);
    FILE *fitxer;
    if((fitxer = fopen(f_output, "w+")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    for(int i = 0; i < mida; i++){
        fprintf(fitxer, "%c", (char)missatge[i]); // *** S'HA DE REMIRAR COM S'ESCRIU AMB TXT *** //
    }
    free(f_output);
    fclose(fitxer);
}
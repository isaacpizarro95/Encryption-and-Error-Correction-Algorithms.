// Processament de l'escriptura del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Obté el nom que tindrà el nou fitxer en el que escriurem
char *nom_foutput(char *f_input, char *afegit){
    char *f_output;
    int check = 0;

    if((f_output = (char *) malloc((strlen(f_input)+3) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    int i, j = 0;

    for(i = 0; i < strlen(f_input); i++){
        f_output[j] = f_input[i];
        if(f_input[i] == '.' && f_input[i+1] != 'R' && check == 0){
            for(int k = 0; k < strlen(afegit); k++){
                j++;
                f_output[j] = afegit[k];
            }
            check = 1;
        }
        j++;
    }
    f_output[j] = '\0';
    return f_output;
}

// Escriu el contingut del missatge en un fitxer '.dat'
void escriure_dat(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *f_output = nom_foutput(f_input, afegit);
    FILE *fitxer;

    if((fitxer = fopen(f_output, "w+")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    for(int i = 0; i < mida; i++){
        if(((i+1) % cols) == 0) fprintf(fitxer, "%d\n", missatge[i]);
        else fprintf(fitxer, "%d ", missatge[i]);
    }
    free(f_output);
    fclose(fitxer);
}

// Escriu el contingut del missatge en un fitxer '.bin'
void escriure_bin(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *f_output = nom_foutput(f_input, afegit);
    FILE *fitxer;

    if((fitxer = fopen(f_output, "wb")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    fwrite(missatge, sizeof(int), mida, fitxer);
    free(f_output);
    fclose(fitxer);
}

// Escriu el contingut del missatge en un fitxer '.txt'
void escriure_txt(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *nou_input;
    const char* bin = ".bin";
    if((nou_input = (char *) malloc((strlen(f_input)+4) * sizeof(char))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    for(int i = 0; i < strlen(f_input); i++) nou_input[i] = f_input[i];
    strncat(nou_input, bin, 4);
    nou_input[strlen(f_input)+4] = '\0';

    char *f_output = nom_foutput(nou_input, afegit);
    FILE *fitxer;

    if((fitxer = fopen(f_output, "wb")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    fwrite(missatge, sizeof(int), mida, fitxer);
    free(nou_input);
    free(f_output);
    fclose(fitxer);
}
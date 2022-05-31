// Gestió dels diferents tipus de fitxer
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

char *tipus_fitxer(char *nom_fitxer){
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(char))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    for(int i = 0; i < 3; i++){
        tipus[i] = nom_fitxer[(strlen(nom_fitxer)-3) + i];
    }    
    return tipus;
}

FILE *gestio_fitxer(char *nom_fitxer, int *apuntador_r){
    FILE *fitxer;
    char *tipus;
    tipus = tipus_fitxer(nom_fitxer);
    if(strcmp(tipus, "bin") == 0){
        if((fitxer = fopen(nom_fitxer, "rb")) == NULL){
            fprintf(stderr, "\n[ERROR]: El fitxer %s no existeix o no es pot obrir...\n\n", nom_fitxer);
            exit(1); 
        }
    }
    else if(strcmp(tipus,"dat") == 0 || strcmp(tipus, "txt") == 0){
        if((fitxer = fopen(nom_fitxer, "r")) == NULL){
            fprintf(stderr, "\n[ERROR]: El fitxer %s no existeix o no es pot obrir...\n\n", nom_fitxer);
            exit(1); 
        }
    }

    // Longitud fitxer
    if(strcmp(tipus, "bin") == 0 || strcmp(tipus, "txt") == 0){
        fseek(fitxer, 0, SEEK_END);
        if(strcmp(tipus, "bin") == 0) *apuntador_r = ftell(fitxer)/4; // Dividim entre 4 perque char ocupa 1 byte i int ocupa 4 bytes
        else *apuntador_r = ftell(fitxer);
        fseek(fitxer, 0, SEEK_SET);
    }
    else longitud_dat(fitxer, apuntador_r);
    free(tipus);
    return fitxer;
}

// Retorna la longitud del missatge a llegir
void longitud_dat(FILE *fitxer, int *apuntador_r){
    int aux = 0;
    int longitud = 0;
    while (!feof(fitxer)){
        fscanf(fitxer, "%d", &aux);
        longitud++;
    }
    *apuntador_r = longitud;
    rewind(fitxer); // Ens coloquem de nou al principi del fitxer
}

// Gestiona la lectura del contingut d'un fitxer depenent del tipus
void gestio_flectura(char *nom_fitxer, FILE *fitxer, int *missatge, int p){
    int i = 0;
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    tipus = tipus_fitxer(nom_fitxer);
    if(strcmp(tipus, "bin") == 0) lectura_bin(fitxer, missatge, p);
    else if(strcmp(tipus, "dat") == 0) lectura_dat(fitxer, missatge, p);
    else if(strcmp(tipus, "txt") == 0) lectura_txt(fitxer, missatge, p);
    free(tipus);
}

// Gestiona l'escriptura del missatge en un nou fitxer depenent del tipus
void gestio_fescriptura(char *f_input, int *missatge, int mida, char *afegit){
    int i = 0;
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    tipus = tipus_fitxer(f_input);
    if(strcmp(tipus, "bin") == 0) escriure_bin(f_input, missatge, afegit);
    else if(strcmp(tipus, "dat") == 0) escriure_dat(f_input, missatge, mida, afegit);
    else if(strcmp(tipus, "txt") == 0) escriure_txt(f_input, missatge, mida, afegit);
    free(tipus);
}
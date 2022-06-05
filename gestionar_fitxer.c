// Gestió dels diferents tipus de fitxer
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Retorna un char * amb el nom del tipus de fitxer= 'dat', 'bin', 'txt'
char *tipus_fitxer(char *nom_fitxer){
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(char))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    int i;
    for(i = 0; i < 3; i++){
        tipus[i] = nom_fitxer[(strlen(nom_fitxer)-3) + i];
    }
    tipus[i] = '\0';
    return tipus;
}

// Obté el fitxer i la llargada d'aquest
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
    else {
        fprintf(stderr, "\n[ERROR]: L'extensió de %s no és correcta. Utilitza .dat, .bin o .txt.\n\n", nom_fitxer);
        exit(1); 
    }

    // Longitud fitxer    
    len_fitxer(fitxer, tipus, apuntador_r);
    free(tipus);
    return fitxer;
}

// Retorna la longitud del missatge.dat a llegir
void len_fitxer(FILE *fitxer, char *tipus, int *apuntador_r){
    int aux = 0;
    int len = 0;
    if(strcmp(tipus, "dat") == 0){
        while(EOF != fscanf(fitxer, "%d", &aux)) len++;
    }
    else if(strcmp(tipus, "txt") == 0) while((fread(&aux, sizeof(char), 1, fitxer)) == 1) len++;
    else while((fread(&aux, sizeof(int), 1, fitxer)) == 1) len++;

    *apuntador_r = len;
    rewind(fitxer); // Ens coloquem de nou al principi del fitxer
}

// Gestiona la lectura del contingut d'un fitxer depenent del tipus
void gestio_flectura(char *nom_fitxer, FILE *fitxer, int *missatge, int p){
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
void gestio_fescriptura(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    tipus = tipus_fitxer(f_input);
    if(strcmp(tipus, "bin") == 0) escriure_bin(f_input, missatge, mida, afegit, cols);
    else if(strcmp(tipus, "dat") == 0) escriure_dat(f_input, missatge, mida, afegit, cols);
    else if(strcmp(tipus, "txt") == 0) escriure_txt(f_input, missatge, mida, afegit, cols);
    free(tipus);
}
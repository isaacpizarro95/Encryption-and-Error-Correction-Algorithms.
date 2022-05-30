// Funcions per gestionar els arguments de la funció main
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Recorre en bucle els arguments rebuts i redirigeix en conseqüència
int arguments(int argc, char *argv[], int *apuntador_p, int *apuntador_k, FILE *fitxer){
    int accio = -1;
    for(int i = 0; i < argc; i++){
        
        if(argv[i][0] == '-') assignacio_p_k(argv[i], apuntador_p, apuntador_k);
        else if(strcmp(argv[i], "codifica") == 0){
            //fitxer = comprova_fitxer(argv[i+1], fitxer);
            accio = 1;
            // Començar la codificació amb el fitxer passant-lo per paràmetre de la funció 'codifica'
        }
        else if(strcmp(argv[i], "descodifica") == 0){
            //fitxer = comprova_fitxer(argv[i+1], fitxer);
            accio = 0;
            // Igual que en codifica pero amb descodifica
        }
        else if(strcmp(argv[i], "configura") == 0){
            // Crear un fitxer de configuració amb els paràmetres de p i k passats pel main
        }
    }
    return accio;
}

void assignacio_p_k(char *argument, int *p, int *k){
    char aux[strlen(argument)-2];
    int i = 0;
    if(argument[1] == 'p'){
        while(argument[i] != '\0'){
            aux[i] = argument[i+3];
            i++;
        }
        if(primer_test(atoi(aux)) == 1) *p = atoi(aux);
        else {
            printf("\n[ERROR] El nombre p ha de ser primer\n\n");
            exit(1);
        }
    }
    else if(argument[1] == 'k'){
        while(argument[i] != '\0'){
            aux[i] = argument[i+3];
            i++;
        }
        *k = atoi(aux);
    }
}

FILE *comprova_fitxer(char *nom, FILE * fitxer){
    // Comprovar el tipus de fitxer: .dat, .bin, .txt
    fitxer = fopen(nom, "r");
    return fitxer;
}
// Funcions per gestionar els arguments de la funció main
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Recorre en bucle els arguments rebuts i redirigeix en conseqüència
char *arguments(int argc, char *argv[], int *apuntador_p, int *apuntador_k, int *accio){
    char *nom_fitxer = "";
    for(int i = 0; i < argc; i++){
        if(argv[i][0] == '-') assignacio_p_k(argv[i], apuntador_p, apuntador_k);
        else if(strcmp(argv[i], "codifica") == 0){
            nom_fitxer = argv[i+1];
            *accio = 0;
        }
        else if(strcmp(argv[i], "descodifica") == 0){
            nom_fitxer = argv[i+1];
            *accio = 1;
        }
        else if(strcmp(argv[i], "configura") == 0){
            *accio = 2;
        }
    }
    return nom_fitxer;
}

// Assigna nous valors a p i k
void assignacio_p_k(char *argument, int *p, int *k){
    char aux[strlen(argument)-2];
    int i = 0;
    while(argument[i] != '\0'){
        int j = 0;
        if(argument[i] == 'p'){
            while(j < (strlen(argument)-2)){
                aux[j] = argument[i+2];
                i++;
                j++;
            }
            *p = atoi(aux);
            return;
        }
        else if(argument[i] == 'k'){
            while(j < (strlen(argument)-2)){
                aux[j] = argument[i+2];
                i++;
                j++;
            }
            *k = atoi(aux);
            return;
        }
        i++;
    }
}

// Revisa que p i k tinguin valors correctes
void check_parametres(int p, int k){
    if(primer_test(p) == 0){
        printf("\n[ERROR] El nombre p ha de ser primer\n\n");
        exit(1);
    }
    if(k+3 > p){
        printf("\n[ERROR] El nombre k ha de ser menor o igual que p-3\n\n");
        exit(1);                
    }
    else if(k <= 1){
        printf("\n[ERROR] El nombre k ha de ser major que 1\n\n");
        exit(1);                 
    }
}
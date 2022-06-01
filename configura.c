// Crea un arxiu de configuració RS-BW.cfg que conté els valors de p i k
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void configura(int p, int k){
    // Creem el fitxer o el sobreescrivim amb permisos de lectura i escriptura
    FILE *fitxer = fopen("RS-BW.cfg", "w+");
    
    // Reservem l'espai de memòria per als strings que contindran a p i k
    char *s_p;
    if((s_p = (char *) malloc(len_n(p) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    char *s_k;
    if((s_k = (char *) malloc(len_n(k) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }

    // Transformem p i k de int a char*
    custom_itoa(p, len_n(p), s_p);
    custom_itoa(k, len_n(k), s_k);

    // Escrivim les dades al fitxer
    fprintf(fitxer, "%s%s\n", "p=", s_p);
    fprintf(fitxer, "%s%s", "k=", s_k);

    // Alliberem la memòria reservada i tanquem el fitxer
    free(s_p);
    free(s_k);
    fclose(fitxer);
}

// Comprovem si existeix l'arxiu de configuració per modificar, si cal, p i k
// *** PROVOCA L'ERROR 'VIOLACIÓN DE SEGMENTO *** //
void comprova_configuracio(int *p, int *k){
    FILE *f_configuracio;
    if((f_configuracio = fopen("RS-BW.cfg", "r")) == NULL){
        //fprintf(stderr, "\n[ERROR]: El fitxer %s no existeix o no es pot obrir...\n\n", "RS-BW.cfg");
        //exit(1);
        return; // Fem return perque no volem que el programa s'acabi si no existeix el fitxer, només és una comprovació
    } 
    llegeix_configuracio(f_configuracio, p, k);
    fclose(f_configuracio);
}

// Llegeix l'arxiu de configuració per obtenir els valors de p i k
void llegeix_configuracio(FILE *fitxer, int *p, int *k){
    char buffer[30];
    while(fgets(buffer, 30, fitxer)){
        // Utilitzem strtok per "trencar la cadena" al arribar a un salt de línia
        strtok(buffer,"\n");
        assignacio_p_k(buffer, p, k);
    }
}

// Funció personalitzada de itoa
void custom_itoa(int n, int len, char *nombre){
    while(n > 0 && len > 0){
        nombre[len-1] = n % 10 +'0';
        n = n / 10;
        len--; 
    }
    //nombre[len_n(n)] = '\0'; /*** Si fico aquesta línia no funciona. Preguntar perque ***/
}

// Retorna la longitud d'un nombre (quantitat de digits)
int len_n(int n){
    int len = 0;
    while(n != 0){
        n = n / 10;
        len++;
    }
    return len;
}
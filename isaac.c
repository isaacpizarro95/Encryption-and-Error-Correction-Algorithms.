// Arxiu gestió programa
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int main(int argc, char *argv[]){
    // Valors per defecte de p i k
    int p = 7; 
    int k = p-3;
    int *apuntador_p = &p;
    int *apuntador_k = &k;
    // Comprovem si existeix l'arxiu de configuració per modificar, si cal, p i k
    FILE *f_configuracio;
    if((f_configuracio= fopen("RS-BW.cfg", "r")) != NULL) {
        llegeix_configuracio(f_configuracio, apuntador_p, apuntador_k);
    }
    fclose(f_configuracio);
    
    // Si accio = 0 codificará, si val 1, descodificará, si val 2 configurará
    int accio = -1;
    int *apuntador_accio = &accio;
    char *nom_fitxer;
    
    // Modifiquem, si és necessari, els valors de p i k a partir dels arguments del main, recollim el valor de acció i obtenim el fitxer
    if(argc > 1){
        nom_fitxer = arguments(argc, argv, apuntador_p, apuntador_k, apuntador_accio);
        check_parametres(p, k);
    }

    if(accio == 0) codificar(p, k, nom_fitxer);
    else if(accio == 1) descodificar(p, k, nom_fitxer);
    else if(accio == 2) configura(p, k);

    return 0;
}
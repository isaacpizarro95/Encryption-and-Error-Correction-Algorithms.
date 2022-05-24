// Trobar l'ordre multiplicatiu d'un element a Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Retorna 0 si no es troba ordre_multiplicatiu, -1 si p no és primer i n en cas de trobar-lo
int ordre_multiplicatiu(int a, int p){
    int n = 1;
    int k = 1;
    
    // Comprovem que el mòdul sigui primer per comprovar que a i p són coprimers
    if(primer_test(p) == 0){
        printf("\n[ERROR] El mòdul ha de ser un nombre primer\n\n");
        return -1;
    }

    while (n < p){
        k = (k * a) % p;
        if(k == 1){
            return n;
        }
        n++;
    }

    return 0;
}
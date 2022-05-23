// Trobar un element primitiu a Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int element_primitiu(int p){
    for(int a = 1; a < p; a++){
        if(ordre_multiplicatiu(a, p) == p - 1){
            return a;
        }
    }
    printf("\nNo s'ha trobat cap element primitiu\n\n");
    return 0;
}
// Comprovació de si un nombre p és primer
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// La funció retorna 1 si el nombre és primer o 0 si no ho és
int primer_test(int p){
    if (p <= 1) {
        printf("\n[ERROR] El nombre ha de ser major o igual a 2\n\n");
        return 0;
    }

    // Si p es divisible per qualsevol nombre entre 2 i p/2, no és primer
    for(int i = 2; i <= p/2; i++){
        if (p % i == 0){
            return 0;
        }
    }

    // Si no és divisible en el rang estudiat implica que és primer
    return 1;
}
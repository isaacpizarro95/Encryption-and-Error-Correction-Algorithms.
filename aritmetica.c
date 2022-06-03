// Funcions d'aritmètica a Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// La funció retorna 1 si el nombre és primer o 0 si no ho és
int primer_test(int p){
    if (p < 3) {
        printf("\n[ERROR] El nombre p ha de ser major que 3\n\n");
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

// Si m es primer, llavors l'invers de a es a elevat a m-2 % m.
// En aquest treball ens serveix el mètode de Fermat perque m sempre és primer.
int teorema_fermat(int a, int potencia_a, int p){
    int invers = 1;
    while(potencia_a > 0){
        // si la potencia és imparell
        if(potencia_a % 2 == 1){
            invers = (invers * a) % p;
        }
        // fem la divisió entera de la potencia entre 2
        potencia_a = (int)(potencia_a / 2);
        // multipliquem la base per si mateixa
        a = (a * a) % p;
    }
    return invers;
}

int invers_a(int a, int p){
    return teorema_fermat(a, p-2, p);
}

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

// Element de fp d'ordre multiplicatiu p-1
int element_primitiu(int p){
    for(int a = 1; a < p; a++){
        if(ordre_multiplicatiu(a, p) == p - 1){
            return a;
        }
    }
    printf("\nNo s'ha trobat cap element primitiu\n\n");
    return 0;
}
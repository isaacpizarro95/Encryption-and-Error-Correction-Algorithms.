// Càlcul de l'invers de a quan m és primer utilitzant el teorema de Fermat
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Si m es primer, llavors l'invers de a es a elevat a m-2 % m.
// En aquest treball ens serveix el mètode de Fermat perque m sempre és primer, sino hauriem d'utilitzar l'algoritme d'Euclides.
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
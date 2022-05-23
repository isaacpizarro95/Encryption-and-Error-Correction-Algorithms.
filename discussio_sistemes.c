// Discussió de sistemes d'equacions lineals a Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// **** REVISAR COM DISCUTEIX EL SISTEMA, A VEGADES S'EQUIVOCA **** //
// Només es calcula la solució de les incògnites si el sistema és compatible determinat
int discussio_sistemes(int p, int files, int cols, double m_ampliada[files][cols]){
    int compatible = 1; // 1 si és compatible i 0 si no ho és
    int determinat = 1; // 1 si és determinat i 0 si no ho és
    for(int i = 0; i < files; i++){
        if(vector_incompatible(cols, m_ampliada[i]) == 1){
            compatible = 0;
        }
        if(vector_nul(cols, m_ampliada[i]) == 1){
            determinat = 0;
        }
    }
    if(compatible == 0){
        printf("\nEl sistema és incompatible i no té solució\n");
    }
    else if(compatible == 1 && determinat == 0){
        printf("\nEl sistema és compatible indeterminat\n");
    }
    else {
        printf("\nEl sistema és compatible determinat i la solucó és:\n\n");
        int x[cols-1];
        int b, invers;

        // Calculem el valor de les incògnites
        for(int i = 0; i < files; i++){
            b = (int)m_ampliada[files-1-i][cols-1]; 
            invers = invers_a(m_ampliada[files-1-i][cols-2-i], p);
            for(int j = cols-2-i; j < cols-2; j++){
                b = ((b + p) - ((x[cols-i-j] * (int)m_ampliada[files-1-i][cols-i-j]) % p) % p);
            }
            x[cols-2-i] = (b * invers) % p;  
        }

        for(int i = 0; i < cols-1; i++){
            printf(" x[%d] = %d\n", i, x[i]);
        }
        printf("\n");
    }
    return 0;
}
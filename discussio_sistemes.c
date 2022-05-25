// Discussió de sistemes d'equacions lineals a Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int discussio_sistemes(int p, int files, int cols, int v_descodificat[cols-1], int m[files][cols]){
    int compatible = 1; // 1 si és compatible i 0 si no ho és
    int determinat = 1; // 1 si és determinat i 0 si no ho és

    for(int i = 0; i < cols-1; i++){
        if(vector_incompatible(cols, m[i]) == 1){
            compatible = 0;
        }
        if(vector_nul(cols, m[i]) == 1){
            determinat = 0;
        }
    }
    if(compatible == 0){
        printf("\nEl sistema és incompatible i no té solució\n");
        exit(1);
    }
    else if(compatible == 1 && determinat == 0){
        printf("\nEl sistema és compatible indeterminat\n");
        exit(1);
    }
    else {
        printf("\nEl sistema és compatible determinat\n\n");
        int b, invers;
        int n_nuls = 0;

        // Calculem el valor de les incògnites
        for(int i = 0; i < files; i++){
            // Si hi ha alguna fila nula al final del sistema la ignorem
            if(vector_nul(cols, m[files-1-i]) == 1){
                n_nuls++;
                continue;
            }
            // b = valor del vector columna de la m_ampliada de la fila actual
            b = m[files-1-i][cols-1]; 
            invers = invers_a(m[files-1-i][cols-2-i+n_nuls], p);
            for(int j = 0; j < i-n_nuls; j++){
                b = ((b + p) - ((v_descodificat[cols-2-j] * m[files-1-i][cols-2-j]) % p)) % p;
            }
            // v_descodificat = valor de les incògnites
            v_descodificat[cols-2-i+n_nuls] = (b * invers) % p;  
        }
    }
    return 0;
}
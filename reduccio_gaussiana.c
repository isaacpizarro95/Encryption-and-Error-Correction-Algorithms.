// Reducció Gaussiana d'una matriu de Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void reduccio_gaussiana(int p, int files, int cols, int m[files][cols]){
    int multiple, invers;

    printf("\nAplicant la reducció Gaussiana...\n");
    for(int j = 0; j <= cols - 2; j++){        

        // Comprovem si hi ha alguna fila nula i si existeix la fiquem al final
        if(vector_nul(files, m[j]) == 1 && j == files - 2){
            intercanvi_files(j, files-1, cols, m);
            continue;
        }
        else if(vector_nul(files, m[j]) == 1){
            intercanvi_files(j, files-1, cols, m);
        }

        // Reduim modul p els coeficients del triangle inferior
        for(int i = j+1; i < files; i++){
            // Si el pivot és 0 i el coeficient de la següent fila en la mateixa columna no ho és, intercanviem les files
            if(m[j][j] == 0 && m[i][j] != 0){
                intercanvi_files(j, i, cols, m);
            }
            // Calculem l'invers del pivot
            invers = invers_a(m[j][j], p);

            // Resolem la equació del tipus: m_ij + (m_jj * múltiple) = 0 (mod p)
            // (m_jj^-1 * m_jj) * múltiple = (((0 + p) - m_ij) * m_jj^-1) % p
            multiple = ((p - m[i][j]) * invers) % p;
            suma_multiple(multiple, p, j, i, cols, m);
        }
    }
    imprimeixmatriu(files, cols, m);
}
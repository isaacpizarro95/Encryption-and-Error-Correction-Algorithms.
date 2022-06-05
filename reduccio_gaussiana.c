// Reducció Gaussiana d'una matriu de Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void reduccio_gaussiana(int p, int files, int cols, int m_ampliada[files][cols]){
    int multiple, invers;

    printf("Apliquem la reducció gaussiana\n");
    for(int j = 0; j < cols-1; j++){
        int i;
        // Comprovem si hi ha alguna fila nula i si existeix la fiquem al final
        if(vector_nul(files, m_ampliada[j]) == 1){
            intercanvi_files(j, files-1, cols, m_ampliada);
            if(j == files -2) continue;
        }
        // Reduim modul p els coeficients del triangle inferior
        for(i = j + 1; i < files; i++){
            // Si el pivot és 0 i el coeficient de la següent fila en la mateixa columna no ho és, intercanviem les files
            if(m_ampliada[j][j] == 0 && m_ampliada[i][j] != 0){
                intercanvi_files(j, i, cols, m_ampliada);
            }
            // Calculem l'invers del pivot
            invers = invers_a(m_ampliada[j][j], p);
            // Resolem la equació del tipus: m_ij + (m_jj * múltiple) = 0 (mod p) => (m_jj^-1 * m_jj) * múltiple = (((0 + p) - m_ij) * m_jj^-1) % p
            multiple = ((p - m_ampliada[i][j]) * invers) % p;
            suma_multiple(multiple, p, j, i, cols, m_ampliada);
        }
    }
    imprimeixmatriu(files, cols, m_ampliada);
}
// Reducció Gaussiana d'una matriu de Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void reduccio_gaussiana(int p, int files, int cols, int v_codificat[files], int v_descodificat[cols-1], int m[files][cols-1]){
    int multiple, invers;
  
    // Per cada vector declarem una nova matriu
    int (*m_ampliada)[cols];
    if((m_ampliada = (int (*)[cols]) malloc((p-1) * cols * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    };
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols-1; j++){
            m_ampliada[i][j] = m[i][j];
        }
        m_ampliada[i][cols-1] = v_codificat[i];
    }

    printf("Apliquem la reducció gaussiana\n");
    for(int j = 0; j < cols-1; j++){
        int i;
        // Comprovem si hi ha alguna fila nula i si existeix la fiquem al final
        if(vector_nul(files, m[j]) == 1 && j == files - 2){
            intercanvi_files(j, files-1, cols, m);
            continue;
        }
        else if(vector_nul(files, m[j]) == 1){
            intercanvi_files(j, files-1, cols, m);
        }
        // Reduim modul p els coeficients del triangle inferior
        for(i = j + 1; i < files; i++){
            // Si el pivot és 0 i el coeficient de la següent fila en la mateixa columna no ho és, intercanviem les files
            if(m_ampliada[j][j] == 0 && m_ampliada[i][j] != 0){
                intercanvi_files(j, i, cols, m);
            }
            // Calculem l'invers del pivot
            invers = invers_a(m_ampliada[j][j], p);
            // Resolem la equació del tipus: m_ij + (m_jj * múltiple) = 0 (mod p)
            // (m_jj^-1 * m_jj) * múltiple = (((0 + p) - m_ij) * m_jj^-1) % p
            multiple = ((p - m_ampliada[i][j]) * invers) % p;
            suma_multiple(multiple, p, j, i, cols, m_ampliada);
        }
    }
    imprimeixmatriu(files, cols, m_ampliada);

    // Discussió del sistema
    discussio_sistemes(p, files, cols, v_descodificat, m_ampliada);
    printf("\n------------------------------------------------------------------------------------------------------------------------\n\n");
    free(m_ampliada);
}
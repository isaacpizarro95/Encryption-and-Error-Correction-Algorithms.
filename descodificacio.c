// Codificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int test_sistemes(int p, int files, int cols, int v_descodificat[cols-1], int m[files][cols]){
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
    }
    else if(compatible == 1 && determinat == 0){
        printf("\nEl sistema és compatible indeterminat\n");
    }
    else {
        printf("\nEl sistema és compatible determinat i la solucó és:\n\n");
        int b, invers;
        int n_nuls = 0;

        // Calculem el valor de les incògnites
        for(int i = 0; i < files; i++){
            if(vector_nul(cols, m[files-1-i]) == 1){
                n_nuls++;
                continue;
            }
            b = m[files-1-i][cols-1]; 
            invers = invers_a(m[files-1-i][cols-2-i+n_nuls], p);
            for(int j = 0; j < i-n_nuls; j++){
                b = ((b + p) - ((v_descodificat[cols-2-j] * m[files-1-i][cols-2-j]) % p)) % p;
            }
            v_descodificat[cols-2-i+n_nuls] = (b * invers) % p;  
        }

        for(int i = 0; i < cols-1; i++){
            printf(" v_descodificat[%d] = %d\n", i, v_descodificat[i]);
        }
        printf("\n");
    }
    return 0;
}

void test_gaussiana(int p, int files, int cols, int v_codificat[files], int v_descodificat[cols-1], int m[files][cols-1]){
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

    for(int j = 0; j < cols-1; j++){
        int i;
        if(vector_nul(files, m[j]) == 1 && j == files - 2){
            intercanvi_files(j, files-1, cols, m);
            continue;
        }
        else if(vector_nul(files, m[j]) == 1){
            intercanvi_files(j, files-1, cols, m);
        }
        for(i = j + 1; i < files; i++){
            if(m_ampliada[j][j] == 0 && m_ampliada[i][j] != 0){
                intercanvi_files(j, i, cols, m);
            }
            invers = invers_a(m_ampliada[j][j], p);
            multiple = ((p - m_ampliada[i][j]) * invers) % p;
            suma_multiple(multiple, p, j, i, cols, m_ampliada);
        }
    }
    imprimeixmatriu(files, cols, m_ampliada);

    // Discussió del sistema
    test_sistemes(p, files, cols, v_descodificat, m_ampliada);
    free(m_ampliada);
}

void descodificacio(int p, int r, int k, int codificat[r/k][p-1], int descodificat[r/k][k], int m[p-1][k], int missatge_descodificat[]){
    // Apliquem la reducció Gaussiana
    for(int i = 0; i < r/k; i++){
        // k+1 a les columnes per afegir la columna b de la matriu ampliada
        test_gaussiana(p, p-1, k+1, codificat[i], descodificat[i], m);
        printf("\n");
    }

    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < k; j++){
            missatge_descodificat[j+l] = descodificat[i][j];
        }
        l += k;
    }
    return;
}
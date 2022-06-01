// Discussió de sistemes d'equacions lineals a Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

int discussio_sistemes(int p, int files, int cols, int v_descodificat[cols-1], int m[files][cols]){
    //int compatible = 1; // 1 si és compatible i 0 si no ho és
    int determinat = 1; // 1 si és determinat i 0 si no ho és
    int files_nules = 0;

    for(int i = 0; i < files; i++){
        if(vector_nul(cols, m[i]) == 1){
            files_nules++;
        }
        if(vector_incompatible(cols, m[i]) == 1){
            printf("\nEl sistema és incompatible\n\n");
            return 0;
        }
    }
    if((files - files_nules) != cols-1) determinat = 0;

    if(determinat == 0){
        printf("\nEl sistema és compatible indeterminat\n\n");
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
    return 1;
}

// Retorna 1 si el vector és nul, és a dir vect = {0, 0, ... , 0} i 0 si no ho és
int vector_nul(int dim, int vect[]){
    for(int i = 0; i < dim; i++){
        if(vect[i] != 0){
            return 0;
        }
    }
    return 1;
}

// Comprova si un vector fa que la matriu sigui incompatible. Retorna 1 si és incompatible i 0 si és compatible
int vector_incompatible(int dim, int vect[]){
    int incompatible = 1;

    // Comprovem que l'últim valor de la fila sigui diferent de 0
    if(vect[dim-1] == 0){
        return 0;
    }

    // Comprovem que la resta de valors de 'i = 0' fins a 'i = dim-1' siguin 0
    for(int i = 0; i < dim-1; i++){
        if(vect[i] != 0){
            incompatible = 0;
        }
    }
    return incompatible;
}


int main(){
    int p = 5;
    int cols = 3;
    
    int m_ampliada[p-1][cols];
    int v[cols-1];
    llegeixmatriu(p, p-1, cols, m_ampliada);
    printf("\n");
    imprimeixmatriu(p-1, cols, m_ampliada);
    discussio_sistemes(p, p-1, cols, v, m_ampliada);
    printf("\nResultat icògnites:\n");
    imprimeixvector(cols-1, v);

    return 0;
}
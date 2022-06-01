// Aplicació de l'algorisme de Berlekamp-Welch
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Inicia l'algorisme de Berlekamp-Welch
void berlekamp_welch(int p, int files, int cols, int v_erroni[files]){
    int e = (files-cols)/2;
    // Declarem la matriu de Berlekamp-Welch
    int (*m)[cols];
    if((m = (int (*)[cols]) malloc((p-1) * (2*e+cols) * sizeof(int))) == NULL){
        printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
        exit(1);
    };
    printf("\nCreem la matriu de codificació\n\n");
    crea_matriu_bw(p, p-1, 2*e+cols, e, v_erroni, m);
    imprimeixmatriu(p-1, 2*e+cols, m);
}

// Crea la matriu de Berlekamp-Welch
void crea_matriu_bw(int p, int files, int cols, int e, int v_erroni[files], int m_bw[files][cols]){
    int a_primitiu = element_primitiu(p);
    for(int i = 0; i < files; i++) {
        int j;
        for(j = 0; j < cols-e; j++) {
            m_bw[i][j] = calcul_potencia(p, a_primitiu, i*j);
        }
        for(j = cols-e; j < cols; j++){
            m_bw[i][j] = ((calcul_potencia(p, a_primitiu, i*(j-cols-e)))*-1)*(v_erroni[i])%p;
        }
    }
}

int main(){
    int p = 11;
    int cols = 5;
    int v[p-1];
    llegeixvector(p, p-1, v);
    imprimeixvector(p-1, v);
    //int m_ampliada[p-1][cols];
    
    /*llegeixmatriu(p, p-1, cols, m_ampliada);
    printf("\n");
    imprimeixmatriu(p-1, cols, m_ampliada);
    discussio_sistemes(p, p-1, cols, v, m_ampliada);
    printf("\nResultat icògnites:\n");
    imprimeixvector(cols-1, v);*/
    berlekamp_welch(p, p-1, cols, v);

    return 0;
}
// Aplicació de l'algorisme de Berlekamp-Welch
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Inicia l'algorisme de Berlekamp-Welch
void berlekamp_welch(int p, int files, int cols, int v_erroni[files]){
    int e = (files-cols)/2;
    int compatible = 2;

    while(compatible == 2){
        // Declarem la matriu de Berlekamp-Welch
        int (*m_bw)[2*e+cols+1];
        if((m_bw = (int (*)[2*e+cols+1]) malloc((files) * (2*e+cols+1) * sizeof(int))) == NULL){
            printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
            exit(1);
        };
        printf("\nCreem la matriu de Berlekamp-Welch ampliada\n\n");
        crea_matriu_bw(p, p-1, 2*e+cols+1, e, v_erroni, m_bw);
        imprimeixmatriu(p-1, 2*e+cols+1, m_bw);

        int *bw_descodificat;
        if((bw_descodificat = (int *) malloc((2*e+cols) * sizeof(int))) == NULL){
            printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
            exit(1);
        }

        // Resolem el sistema d'equacions
        reduccio_gaussiana(p, files, 2*e+cols+1, m_bw);
        compatible = discussio_sistemes(p, p-1, 2*e+cols+1, bw_descodificat, m_bw);
        if(compatible == 0){
            printf("Error no corregible\n\n");
            exit(1);
        }
        if(compatible == 1) sistema_bw(p, p-1, 2*e+cols+1, bw_descodificat);
        if(compatible == 2) e -= 1;
        free(m_bw);
        free(bw_descodificat);

        printf("\n------------------------------------------------------------------------------------------------------------------------\n\n");
    }
}

// Crea la matriu de Berlekamp-Welch
void crea_matriu_bw(int p, int files, int cols, int e, int v_erroni[files], int m_bw[files][cols]){
    int a_primitiu = element_primitiu(p);
    for(int i = 0; i < files; i++) {
        int j;
        for(j = 0; j < cols-e-1; j++) {
            m_bw[i][j] = calcul_potencia(p, a_primitiu, i*j);
        }
        for(j = cols-e-1; j < cols-1; j++){
            m_bw[i][j] = ((calcul_potencia(p, a_primitiu, i*(j-cols-e-1)))*-1)*(v_erroni[i]) % p;
        }
        m_bw[i][cols-1] = ((calcul_potencia(p, a_primitiu, (i*e))) * v_erroni[i]) % p;
    }
}

void sistema_bw(int p, int e, int cols, int bw_descodificat[]){
    int compatible;
    int (*ms_bw)[cols-(2*e)];
    if((ms_bw = (int (*)[cols-(2*e)]) malloc((cols-e-1) * (cols-(2*e)) * sizeof(int))) == NULL){
        printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
        exit(1);
    };
    crea_ms_bw(p, cols-e-1, cols-2*e, bw_descodificat, ms_bw);
    compatible = discussio_sistemes(p, cols-e-1, cols-2*e, bw_descodificat, ms_bw);
    if(compatible == 0){
        printf("Error no corregible\n\n");
        exit(1);
    }
    free(ms_bw);
}

// Crea la matriu del sistema Berlekamp-Welch quan es compatible determinat
void crea_ms_bw(int p, int files, int cols, int bw_descodificat[files], int ms_bw[files][cols]){
    int k = 0;
    for(int i = 0; i < files; i++){
        int j;
        // Añadir condición para los 1 y zeros de la izquierda. Igual se necesita 'e'
        /* if(k > ...){
            for()
        }*/
        for(j = 0; j < i+1; j++){
            ms_bw[i][j] = bw_descodificat[k-j]; // Els valors no son aquests, estaries agafant 'g' no 'f'. Les 'f' estan al final
        }
        for(j; j < cols; j++){
            ms_bw[i][j] = 0;
        }
        k++;
    }
}

/*
int main(){
    int p = 11;
    int cols = 5;
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //llegeixvector(p, p-1, v);
    printf("\nVector erroni\n\n");
    imprimeixvector(p-1, v);

    berlekamp_welch(p, p-1, cols, v);

    return 0;
}*/
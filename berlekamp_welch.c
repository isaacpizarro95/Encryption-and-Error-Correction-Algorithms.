// Aplicació de l'algorisme de Berlekamp-Welch
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// Inicia l'algorisme de Berlekamp-Welch
void berlekamp_welch(int p, int files, int cols, int v_erroni[files], int descodificat[]){
    int e = (files-cols)/2;
    int compatible = 2; // El valor de compatible s'inicialitza com a compatible indeterminat

    // Mentre el sistema que obtenim sigui compatible indeterminat repetim i restem 1 a e
    while(compatible == 2){
        // Creem la matriu de Berlekamp-Welch
        int (*m_bw)[2*e+cols+1];
        if((m_bw = (int (*)[2*e+cols+1]) malloc((files) * (2*e+cols+1) * sizeof(int))) == NULL){
            printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
            exit(1);
        };
        printf("\nCreem la matriu de Berlekamp-Welch ampliada\n\n");
        crea_matriu_bw(p, p-1, 2*e+cols+1, e, v_erroni, m_bw);
        imprimeixmatriu(p-1, 2*e+cols+1, m_bw);

        // Vector que contindrà els valors de les incògnites
        int *bw_incognites;
        if((bw_incognites = (int *) malloc((2*e+cols) * sizeof(int))) == NULL){
            printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
            exit(1);
        }

        // Resolem el sistema d'equacions
        reduccio_gaussiana(p, files, 2*e+cols+1, m_bw);
        compatible = discussio_sistemes(p, p-1, 2*e+cols+1, bw_incognites, m_bw);
        if(compatible == 0){
            printf("Error no corregible\n\n");
            exit(1);
        }
        // Si el sistema és compatible determinat construim un nou sistema a partir de bw_incognites
        if(compatible == 1) sistema_bw(p, e, 2*e+cols+1, bw_incognites, descodificat);

        // Si el sistema és compatible indeterminat e=e-1 i repetim el procés
        if(compatible == 2) e -= 1;
        free(m_bw);
        free(bw_incognites);
    }
}

// Crea la matriu ampliada de Berlekamp-Welch
void crea_matriu_bw(int p, int files, int cols, int e, int v_erroni[files], int m_bw[files][cols]){
    int a_primitiu = element_primitiu(p);
    for(int i = 0; i < files; i++) {
        int j;
        for(j = 0; j < cols-e-1; j++) {
            m_bw[i][j] = calcul_potencia(p, a_primitiu, i*j);
        }
        int k = 0;
        for(j = cols-e-1; j < cols-1; j++){
            m_bw[i][j] = (p-((calcul_potencia(p, a_primitiu, i*k)) % p))*(v_erroni[i]) % p;
            k++;
        }
        m_bw[i][cols-1] = ((calcul_potencia(p, a_primitiu, i*cols-1) % p) * v_erroni[i]) % p;
    }
    printf("\n");
}

// Crea sistema a partir de la bw_icognites
void sistema_bw(int p, int e, int cols, int bw_incognites[], int descodificat[]){
    int compatible;

    // Matriu del sistema
    int (*ms_bw)[cols-(2*e)];
    if((ms_bw = (int (*)[cols-(2*e)]) malloc((cols-e-1) * (cols-(2*e)) * sizeof(int))) == NULL){
        printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
        exit(1);
    };
    crea_ms_bw(p, e, cols-e-1, cols-2*e-1, bw_incognites, ms_bw);
    
    compatible = discussio_sistemes(p, cols-e-1, cols-2*e, descodificat, ms_bw);
    if(compatible == 0){
        printf("Error no corregible\n\n");
        exit(1);
    }
    if(compatible == 1) {
        printf("L'algorisme de Berlekamp-Welch ha corregit amb èxit els errors i el vector ara descodificat és:\n\n");
        imprimeixvector(cols-e-2, descodificat);
    }
    free(ms_bw);
}

// Crea la matriu del sistema Berlekamp-Welch quan és compatible determinat
void crea_ms_bw(int p, int e, int files, int cols, int bw_incognites[], int ms_bw[files][cols+1]){
    int i = 0;

    for(int j = 0; j < cols; j++){
        if(j > 0){
            for(int k = 0; k < j; k++){
                ms_bw[k][j] = 0;
            }
        }   
        for(i = 0; i < e; i++){
            ms_bw[i+j][j] = bw_incognites[2*e + cols + i - 1];
        }

        ms_bw[i+j][j] = 1;
        for(int z = i+j+1; z < files; z++){
            ms_bw[z][j] = 0;
        }
    }
    for(int t = 0; t < files; t++){
        ms_bw[t][cols] = bw_incognites[t];
    } 

    printf("\nMatriu de solució del sistema de Berlekamp-Welch:\n\n");
    imprimeixmatriu(files, cols+1, ms_bw);
}
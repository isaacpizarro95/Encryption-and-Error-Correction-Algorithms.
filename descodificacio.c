// Descodificació del missatge
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void descodificar(int p, int k, char *nom_fitxer){
    // Declarem la matriu de Vandermonde
    int (*m)[k];
    if((m = (int (*)[k]) malloc((p-1) * k * sizeof(int))) == NULL){
        printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
        exit(1);
    };
    printf("\nCreem la matriu de codificació\n\n");
    crea_matriu_vandermonde(p, p-1, k, m);
    imprimeixmatriu(p-1, k, m);
    
    // Llegim missatge
    FILE *fitxer;
    int r; // Longitud missatge
    int *apuntador_r = &r;
    fitxer = gestio_fitxer(nom_fitxer, apuntador_r);

    // Guardem el missatge codificat
    int *missatge_codificat;
    if((missatge_codificat = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    gestio_flectura(nom_fitxer, fitxer, missatge_codificat, p);
    printf("\nMissatge codificat\n");
    imprimeixvector(r, missatge_codificat);

    int (*codificat)[p-1];
    if((codificat = (int (*)[p-1]) malloc((r/(p-1)) * (p-1) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }

    // Dividim en vectors el missatge codificat guardant-lo com a matriu
    dividir_missatge(r/(p-1), p-1, missatge_codificat, codificat);
    printf("\nMatriu codificada\n");
    imprimeixmatriu(r/(p-1), p-1, codificat);
    printf("\n");

    // Creem la matriu i el missatge de descodificació
    int (*descodificat)[k];
    if((descodificat = (int (*)[k]) malloc((r/(p-1)) * k * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }
    int *missatge_descodificat;
    if((missatge_descodificat = (int *) malloc(((r/(p-1)) * k) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }

    // A partir de la matriu codificada i la matriu de codificació trobem el missatge codificat
    printf("\nDescodifiquem el missatge\n\n");
    descodificacio(p, r/(p-1), k, codificat, descodificat, m, missatge_descodificat);
    printf("\nMatriu descodificada\n");
    imprimeixmatriu((r/(p-1)), k, descodificat);
    printf("\nMissatge descodificat\n");
    imprimeixvector(((r/(p-1))*k), missatge_descodificat);
    printf("\n");

    // Escrivim el missatge descodificat en un nou fitxer
    gestio_fescriptura(nom_fitxer, missatge_descodificat, (r/(p-1))*k, "BW.", k);

    // Alliberem la memòria que haviem reservat
    fclose(fitxer);
    free(missatge_codificat);
    free(codificat);
    free(missatge_descodificat);
    free(descodificat);
    free(m);
}

void descodificacio(int p, int files, int cols, int codificat[files][p-1], int descodificat[files][cols], int m[p-1][cols], int missatge_descodificat[]){
    int compatible;
    
    // Apliquem la reducció Gaussiana
    for(int i = 0; i < files; i++){
        // cols+1 per afegir la columna b de la matriu ampliada
        // Per cada vector declarem una nova matriu
        int (*m_ampliada)[cols+1];
        if((m_ampliada = (int (*)[cols+1]) malloc((p-1) * (cols+1) * sizeof(int))) == NULL){
            printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
            exit(1);
        };
        for(int j = 0; j < (p-1); j++){
            for(int k = 0; k < cols; k++){
                m_ampliada[j][k] = m[j][k];
            }
            m_ampliada[j][cols] = codificat[i][j];
        }
        reduccio_gaussiana(p, p-1, cols+1, m_ampliada);
        
        // Discussió del sistema retorna 1 si el sistema és compatible determinat i 0 si és incompatible
        compatible = discussio_sistemes(p, p-1, cols+1, descodificat[i], m_ampliada, 0);
        if(compatible == 0){
            // Si el sistema és incompatible apliquem l'algorisme de correcció d'errors de Berlekamp-Welch
            berlekamp_welch(p, p-1, cols, codificat[i], descodificat[i]);
        }
        printf("descodificat[%d] = \t", i);
        imprimeixvector(cols, descodificat[i]);
        // Sistema compatible indeterminat
        if(compatible == 2){
            exit(1);
        }
        free(m_ampliada);
        
        printf("\n------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    int l = 0;
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            missatge_descodificat[j+l] = descodificat[i][j];
        }
        l += cols;
    }
    return;
}
// Reducció Gaussiana d'una matriu de Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

// **** AMB MATRIUS GRANS NO FA BÉ LA REDUCCIÓ **** //
void reduccio_gaussiana(int p, int files, int cols, int m_ampliada[files][cols]){
    int multiple, invers;

    printf("\nAplicant la reducció Gaussiana...\n");
    for(int j = 0; j <= cols - 2; j++){        

        // Comprovem si hi ha alguna fila nula i si existeix la fiquem al final
        if(vector_nul(files, m_ampliada[j]) == 1 && j == files - 2){
            intercanvi_files(j, files-1, cols, m_ampliada);
            continue;
        }
        else if(vector_nul(files, m_ampliada[j]) == 1){
            intercanvi_files(j, files-1, cols, m_ampliada);
        }

        // Reduim modul p els coeficients del triangle inferior
        for(int i = j+1; i < files; i++){
            if(m_ampliada[j][j] == 0 && m_ampliada[i][j] != 0){
                intercanvi_files(j, i, cols, m_ampliada);
                //continue;
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
}

int main()
{
    int n = 14;
	int p = 5;
    int m_ampliada[n][n+1];

	/* 1. Llegint matriu aumentada */
    printf("\nLlegint matriu aumentada...\n");
	llegeixmatriu(p, n, n+1, m_ampliada);
    imprimeixmatriu(n, n+1, m_ampliada); 

    /* 2. Aplicant la reducció Gaussiana */
    reduccio_gaussiana(p, n, n+1, m_ampliada);

    /* 3. Discussió del sistema */
    discussio_sistemes(p, n, n+1, m_ampliada);

	return(0);
}
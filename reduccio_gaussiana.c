// Reducció Gaussiana d'una matriu de Fp
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include "isaac.h"

void reduccio_gaussiana(int p, int files, int cols, double m_ampliada[files][cols]){
    double multiple;

    /* Aplicant la reducció Gaussiana */
    printf("\nAplicant la reducció Gaussiana...\n");

    // Per calcular el múltiple hem de tenir en compte que s'ha d'aconseguir que la suma sigui igual a p.
    // Es a dir m[i][j] + multiple * m[j][j] = p => multiple = (p - m[i][j]) / m[j][j]

    // ******* FALTA REVISAR DE NOU LA MATRIU PER VEURE SI FALTEN ZEROS PER FICAR FENT INTERCANVIS I TRANSFORMACIONS DE FILES ****** //
    for(int j = 0; j < cols/2; j++){
        for(int i = j+1; i < files; i++){
            if(m_ampliada[j][j] == 0 && m_ampliada[i][j] != 0){
                intercanvi_files(j, i, cols, m_ampliada);
                //continue;
            }
            multiple = (p - m_ampliada[i][j]) / m_ampliada[j][j];
            suma_multiple(multiple, p, j, i, cols, m_ampliada);
  
        }
    }

    // Comprovem si hi ha alguna fila nula i si existeix la fiquem al final
    for(int i = 1; i < files; i++){
        if(vector_nul(files, m_ampliada[i]) == 1) {
            intercanvi_files(i, files-1, cols, m_ampliada);
        } 
    }
    imprimeixmatriu(files, cols, m_ampliada);
}

int main()
{
    int n = 2;
	int p = 7;

    double m_ampliada[n][n+1];

	/* 2. Llegint matriu aumentada */
    printf("\nLlegint matriu aumentada...\n");
	llegeixmatriu(n, n+1, m_ampliada);
    imprimeixmatriu(n, n+1, m_ampliada);
    
    reduccio_gaussiana(p, n, n+1, m_ampliada);
    discussio_sistemes(p, n, n+1, m_ampliada);

	return(0);
}
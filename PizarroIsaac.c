// Treball C - Algorismes de Reed-Solomon i Berlekamp-Welch
// Autor: Isaac Pizarro Contreras
// NIU: 1636421

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aritmètica a Fp
int primer_test(int p);
int invers_a(int a, int p);
int ordre_multiplicatiu(int a, int p);
int element_primitiu(int p);

// Àlgebra Lineal
void llegeixvector(int p, int dim, int vect[]);
void llegeixmatriu(int p, int files, int cols, int m[][cols]);
void imprimeixvector(int dim, int vect[]);
void imprimeixmatriu(int files, int cols, int m[][cols]);
void vectorxescalar(int dim, int a, int p, int vector[], int resul[]);
void filaxescalar(int a, int p, int fila, int cols, int m[][cols]);
void intercanvi_files(int fila_inici, int fila_desti, int cols, int m[][cols]);
void suma_multiple(int multiple, int p, int fila_inici, int fila_desti, int cols, int m[][cols]);
void matriuxvector(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]);

// Reducció gaussiana i discussió de sistemes
void reduccio_gaussiana(int p, int files, int cols, int m_ampliada[files][cols]);
int discussio_sistemes(int p, int files, int cols, int v_descodificat[], int m[files][cols], int e);
int vector_nul(int dim, int vect[]);
int vector_incompatible(int dim, int vect[]);

// Codificació i Descodificació
void codificar(int p, int k, char *nom_fitxer);
void codificacio(int p, int r, int k, int paraula[r/k][k], int codificat[r/k][p-1], int m[p-1][k], int missatge_codificat[]);
void descodificar(int p, int k, char *nom_fitxer);
void descodificacio(int p, int files, int cols, int codificat[files][p-1], int descodificat[files][cols], int m[p-1][cols], int missatge_descodificat[]);

// Utils codificació-descodificació
int calcul_potencia(int p, int a, int potencia);
void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]);
void dividir_missatge(int files, int cols, int missatge[], int paraules[files][cols]);
int *realloc_missatge(int aux_r, int r, int *missatge);

// Berlekamp-Welch
void berlekamp_welch(int p, int files, int cols, int v_erroni[files], int descodificat[]);
void crea_matriu_bw(int p, int files, int cols, int e, int v_erroni[files], int m_bw[files][cols]);
void sistema_bw(int p, int e, int cols, int bw_incognites[], int descodificat[]);
void crea_ms_bw(int p, int e, int files, int cols, int bw_incognites[], int ms_bw[files][cols+1]);

// Arguments
char *arguments(int argc, char *argv[], int *apuntador_p, int *apuntador_k, int *accio);
void assignacio_p_k(char *argument, int *p, int *k);
void check_parametres(int p, int k);

// Fitxers
FILE *gestio_fitxer(char *nom_fitxer, int *apuntador_r);
char *tipus_fitxer(char *nom_fitxer);

// Lectura fitxers
void len_fitxer(FILE *fitxer, char *tipus, int *apuntador_r);
void gestio_flectura(char *nom_fitxer, FILE *fitxer, int *missatge, int p);
void lectura_bin(FILE *fitxer, int *missatge, int p);
void lectura_dat(FILE *fitxer, int *missatge, int p);
void lectura_txt(FILE *fitxer, int *missatge, int p);

// Escriptura fitxers
char *nom_foutput(char *f_input, char *afegit);
void gestio_fescriptura(char *f_input, int *missatge, int mida, char *afegit, int cols);
void escriure_bin(char *f_input, int *missatge, int mida, char *afegit, int cols);
void escriure_dat(char *f_input, int *missatge, int mida, char *afegit, int cols);
void escriure_txt(char *f_input, int *missatge, int mida, char *afegit, int cols);

// Configuració
void configura(int p, int k);
void comprova_configuracio(int *p, int *k);
void llegeix_configuracio(FILE *fitxer, int *p, int *k);
int len_n(int n);
void custom_itoa(int n, int len, char *nombre);


// ****************************************************************************** //
// ****************************** INICI PROGRAMA ******************************** //
// ****************************************************************************** //

int main(int argc, char *argv[]){
    // Valors per defecte de p i k
    int p = 257; 
    int k = 200;
    int *apuntador_p = &p;
    int *apuntador_k = &k;

    // Comprovem si existeix l'arxiu de configuració per modificar, si cal, p i k
    comprova_configuracio(apuntador_p, apuntador_k);
    
    // Si accio = 0 codificará, si val 1, descodificará, si val 2 configurará
    int accio = -1;
    int *apuntador_accio = &accio;
    char *nom_fitxer;
    
    // Modifiquem, si és necessari, els valors de p i k a partir dels arguments del main, recollim el valor de acció i obtenim el fitxer
    if(argc > 1) nom_fitxer = arguments(argc, argv, apuntador_p, apuntador_k, apuntador_accio);
    check_parametres(p, k);

    if(accio == 0) codificar(p, k, nom_fitxer);
    else if(accio == 1) descodificar(p, k, nom_fitxer);
    else if(accio == 2) configura(p, k);
    
    return 0;
}

// Comprovem si existeix l'arxiu de configuració per modificar, si cal, p i k
void comprova_configuracio(int *p, int *k){
    FILE *f_configuracio;
    if((f_configuracio = fopen("RS-BW.cfg", "r")) == NULL){
        return; // Fem return perque no volem que el programa s'acabi si no existeix el fitxer, només és una comprovació
    } 
    llegeix_configuracio(f_configuracio, p, k);
    fclose(f_configuracio);
}

// Llegeix l'arxiu de configuració per obtenir els valors de p i k
void llegeix_configuracio(FILE *fitxer, int *p, int *k){
    char buffer[30];
    while(fgets(buffer, 30, fitxer)){
        // Utilitzem strtok per "trencar la cadena" al arribar a un salt de línia
        strtok(buffer,"\n");
        assignacio_p_k(buffer, p, k);
    }
}

// Recorre en bucle els arguments rebuts i redirigeix en conseqüència
char *arguments(int argc, char *argv[], int *apuntador_p, int *apuntador_k, int *accio){
    char *nom_fitxer = "";
    for(int i = 0; i < argc; i++){
        if(argv[i][0] == '-') assignacio_p_k(argv[i], apuntador_p, apuntador_k);
        else if(strcmp(argv[i], "codifica") == 0){
            nom_fitxer = argv[i+1];
            *accio = 0;
        }
        else if(strcmp(argv[i], "descodifica") == 0){
            nom_fitxer = argv[i+1];
            *accio = 1;
        }
        else if(strcmp(argv[i], "configura") == 0){
            *accio = 2;
        }
    }
    return nom_fitxer;
}

// Assigna nous valors a p i k
void assignacio_p_k(char *argument, int *p, int *k){
    char aux[strlen(argument)-2];
    int i = 0;
    while(argument[i] != '\0'){
        int j = 0;
        if(argument[i] == 'p'){
            while(j < (strlen(argument)-2)){
                aux[j] = argument[i+2];
                i++;
                j++;
            }
            *p = atoi(aux);
            return;
        }
        else if(argument[i] == 'k'){
            while(j < (strlen(argument)-2)){
                aux[j] = argument[i+2];
                i++;
                j++;
            }
            *k = atoi(aux);
            return;
        }
        i++;
    }
}

// Revisa que p i k tinguin valors correctes
void check_parametres(int p, int k){
    if(primer_test(p) == 0){
        printf("\n[ERROR] El nombre p ha de ser primer\n\n");
        exit(1);
    }
    if (p <= 3) {
        printf("\n[ERROR] El nombre p ha de ser major que 3\n\n");
        exit(1);
    }
    if(k+3 > p){
        printf("\n[ERROR] El nombre k ha de ser menor o igual que p-3\n\n");
        exit(1);                
    }
    if(k <= 1){
        printf("\n[ERROR] El nombre k ha de ser major que 1\n\n");
        exit(1);                 
    }
}


// **** CODIFICACIÓ  **** //

void codificar(int p, int k, char *nom_fitxer){
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

    // Guardem el missatge
    int *missatge; 
    if((missatge = (int *) malloc(r * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    gestio_flectura(nom_fitxer, fitxer, missatge, p);
    printf("\n\nMissatge\n");
    imprimeixvector(r, missatge);

    // Si r no és múltiple de k
    if(r % k != 0){
        int aux_r = r;
        r = (r + k) - (r % k);
        missatge = realloc_missatge(aux_r, r, missatge);
        printf("\n\nMissatge redimensionat per a que 'r' sigui múltiple de 'k'\n\n");
        imprimeixvector(r, missatge);
    }

    // Dividim en vectors el missatge guardant-lo com a matriu
    printf("\n\nDividim el missatge en vectors\n\n");
    int (*paraules)[k];
    if((paraules = (int (*)[k]) malloc((r/k) * k * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    };
    dividir_missatge(r/k, k, missatge, paraules);
    imprimeixmatriu(r/k, k, paraules);

    // Codifiquem el missatge
    printf("\n\nCodifiquem el missatge\n\n");
    int (*codificat)[p-1];
    if((codificat = (int (*)[p-1]) malloc((r/k) * (p-1) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);        
    }
    int *missatge_codificat;
    if((missatge_codificat = (int *) malloc(((r/k)*(p-1)) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    codificacio(p, r, k, paraules, codificat, m, missatge_codificat);
    imprimeixmatriu(r/k, p-1, codificat);
    printf("\n\nMissatge codificat\n\n");
    imprimeixvector(((r/k)*(p-1)), missatge_codificat);

    // Escrivim el missatge codificat en un nou fitxer
    gestio_fescriptura(nom_fitxer, missatge_codificat, (r/k)*(p-1), "RS.", p-1);
    
    fclose(fitxer);
    free(paraules);
    free(missatge_codificat);
    free(codificat);
    free(missatge);
    free(m);
}

// Crea el missatge codificat
void codificacio(int p, int r, int k, int paraula[r/k][k], int codificat[r/k][p-1], int m[p-1][k], int missatge_codificat[]){
    for(int i = 0; i < r/k; i++){
        matriuxvector(p, p-1, k, paraula[i], codificat[i], m);
    }

    int l = 0;
    for(int i = 0; i < r/k; i++){
        for(int j = 0; j < p-1; j++){
            missatge_codificat[j+l] = codificat[i][j];
        }
        l += p-1;
    }
    return;
}

// Crea la matriu de codificació
void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]){
    int a_primitiu = element_primitiu(p);
    for(int i = 0; i < files; i++) {
        for(int j = 0; j < cols; j++) {
            m[i][j] = calcul_potencia(p, a_primitiu, i*j);
        }
    }
    return;
}

// Calcula (a^potencia) % mòdul p
int calcul_potencia(int p, int a, int potencia){
    int a_final = a;

    // Reduim l'exponent sabent que a^(p-1) = 1 (mod p)
    potencia = potencia % (p-1);

    // Calculem la potència
    if(potencia == 0){
        return 1;
    }
    for(int i = 1; i < potencia; i++){
        a_final = (a_final * a) % p;
    }
    a_final = a_final % p;
    return a_final;
}

// Redimensionem el tamany del missatge en cas de que la seva longitud no sigui divisible per k
int *realloc_missatge(int aux_r, int r, int *missatge){
    int *nou_missatge;
    
    if((nou_missatge = (int *) realloc (missatge, r * sizeof(int))) == NULL){
        printf("[ERROR] Realloc no ha pogut redimensionar l'espai de memòria\n");
        exit(1);        
    };

    for(int i = aux_r; i < r; i++){
        nou_missatge[i] = 0; 
    }

    missatge = nou_missatge;
    return missatge;
}

// Divideix el missatge en paraules(vectors) formant una matriu de paraules
void dividir_missatge(int files, int cols, int missatge[], int paraules[files][cols]){
    int l = 0;
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            paraules[i][j] = missatge[j+l];
        }
        l += cols;
    }
    return;
}


// **** DESCODIFICACIÓ  **** //

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

// Esglaona inferiorment una matriu ampliada
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
            // Resolem la equació del tipus: m_ij + (m_jj * múltiple) = 0 (mod p) => (m_jj^-1 * m_jj) * múltiple = ((p - m_ij) * m_jj^-1) % p
            multiple = ((p - m_ampliada[i][j]) * invers) % p;
            suma_multiple(multiple, p, j, i, cols, m_ampliada);
        }
    }
    imprimeixmatriu(files, cols, m_ampliada);
}

// Discuteix un sistema d'equacions lineals
int discussio_sistemes(int p, int files, int cols, int v_descodificat[], int m[files][cols], int e){
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
    // Si rang(m) != nombre d'incògnites serà compatible indeterminat
    if((files - files_nules) != cols-1 && e == 0) determinat = 0; 
    if(determinat == 0){
        printf("\nEl sistema és compatible indeterminat\n\n");
        return 2;
    }
    else {
        printf("\nEl sistema és compatible determinat\n\n");
        
        int b, invers;
        int n_nuls = 0; // Nombre de files nul·les

        // Calculem el valor de les incògnites
        // Restem e perque les mides de les matrius de solució de BW estan modulades per e
        for(int i = 0; i < files-e; i++){
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
        printf("\nCreem la matriu de Berlekamp-Welch ampliada amb e = %d\n\n", e);
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
        compatible = discussio_sistemes(p, p-1, 2*e+cols+1, bw_incognites, m_bw, 0);
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
        m_bw[i][cols-1] = ((calcul_potencia(p, a_primitiu, i*e) % p) * v_erroni[i]) % p;
    }
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
    
    compatible = discussio_sistemes(p, cols-e-1, cols-2*e, descodificat, ms_bw, e);
    if(compatible == 0){
        printf("Error no corregible\n\n");
        exit(1);
    }
    if(compatible == 1) {
        printf("L'algorisme de Berlekamp-Welch ha corregit amb èxit els errors i el vector ara descodificat és:\n\n");
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
            ms_bw[i+j][j] = bw_incognites[e + cols + i];
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


// **** GESTIÓ FITXERS **** //

// Obté el fitxer i la llargada d'aquest
FILE *gestio_fitxer(char *nom_fitxer, int *apuntador_r){
    FILE *fitxer;
    char *tipus;
    tipus = tipus_fitxer(nom_fitxer);
    if(strcmp(tipus, "bin") == 0){
        if((fitxer = fopen(nom_fitxer, "rb")) == NULL){
            fprintf(stderr, "\n[ERROR]: El fitxer %s no existeix o no es pot obrir...\n\n", nom_fitxer);
            exit(1); 
        }
    }
    else if(strcmp(tipus,"dat") == 0 || strcmp(tipus, "txt") == 0){
        if((fitxer = fopen(nom_fitxer, "r")) == NULL){
            fprintf(stderr, "\n[ERROR]: El fitxer %s no existeix o no es pot obrir...\n\n", nom_fitxer);
            exit(1); 
        }
    }
    else {
        fprintf(stderr, "\n[ERROR]: L'extensió de %s no és correcta. Utilitza .dat, .bin o .txt.\n\n", nom_fitxer);
        exit(1); 
    }

    // Longitud fitxer    
    len_fitxer(fitxer, tipus, apuntador_r);
    free(tipus);
    return fitxer;
}

// Retorna un char * amb el nom del tipus de fitxer= 'dat', 'bin', 'txt'
char *tipus_fitxer(char *nom_fitxer){
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(char))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    int i;
    for(i = 0; i < 3; i++){
        tipus[i] = nom_fitxer[(strlen(nom_fitxer)-3) + i];
    }
    tipus[i] = '\0';
    return tipus;
}

// Retorna la longitud del missatge.dat a llegir
void len_fitxer(FILE *fitxer, char *tipus, int *apuntador_r){
    int aux = 0;
    int len = 0;
    if(strcmp(tipus, "dat") == 0){
        while(EOF != fscanf(fitxer, "%d", &aux)) len++;
    }
    else if(strcmp(tipus, "txt") == 0) while((fread(&aux, sizeof(char), 1, fitxer)) == 1) len++;
    else while((fread(&aux, sizeof(int), 1, fitxer)) == 1) len++;

    *apuntador_r = len;
    rewind(fitxer); // Ens coloquem de nou al principi del fitxer
}

// Gestiona la lectura del contingut d'un fitxer depenent del tipus
void gestio_flectura(char *nom_fitxer, FILE *fitxer, int *missatge, int p){
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    tipus = tipus_fitxer(nom_fitxer);
    if(strcmp(tipus, "bin") == 0) lectura_bin(fitxer, missatge, p);
    else if(strcmp(tipus, "dat") == 0) lectura_dat(fitxer, missatge, p);
    else if(strcmp(tipus, "txt") == 0) lectura_txt(fitxer, missatge, p);
    free(tipus);
}

// Llegeix el missatge d'un fitxer bin
void lectura_bin(FILE *fitxer, int *missatge, int p){
    int i = 0;
    int warning = 0;
    while((fread(&missatge[i], sizeof(int), 1, fitxer)) == 1){
        if(missatge[i] >= p){
            warning += 1;
            missatge[i] = missatge[i] % p;
        }
        i++;
    }
    if(warning != 0) fprintf(stderr, "\n[Warning]: El fitxer té %d valors >= p. Es reduirà mòdul p\n\n", warning);
}

// Llegeix el missatge d'un fitxer dat
void lectura_dat(FILE *fitxer, int *missatge, int p){
    int i = 0;
    int warning = 0;

    // Guardem els valors en 'missatge'
    while(EOF != fscanf(fitxer, "%d", &(missatge[i]))){
        if(missatge[i] >= p){
            warning += 1;
            missatge[i] = missatge[i] % p;
        }
        i++;
    }
    if(warning != 0) fprintf(stderr, "\n[Warning]: El fitxer té %d valors >= p. Es reduirà mòdul p\n\n", warning);
    rewind(fitxer);
}

// Llegeix el missatge d'un fitxer txt
void lectura_txt(FILE *fitxer, int *missatge, int p){
    char c;
    int i = 0;
    int warning = 0;
    if(p < 257){
        fprintf(stderr, "\n[ERROR] Si el fitxer és del tipus .txt p ha de ser major o igual que 257\n\n");
        exit(1);
    }
    while((c = fgetc(fitxer)) != EOF){
        missatge[i] = (int)c;
        if(missatge[i] >= p){
            warning += 1;
            missatge[i] = missatge[i] % p;
        }
        i++;
    }
    if(warning != 0) fprintf(stderr, "\n[Warning]: El fitxer té %d valors >= p. Es reduirà mòdul p\n\n", warning);
}

// Gestiona l'escriptura del missatge en un nou fitxer depenent del tipus
void gestio_fescriptura(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *tipus;
    if((tipus = (char *) malloc(3 * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    tipus = tipus_fitxer(f_input);
    if(strcmp(tipus, "bin") == 0) escriure_bin(f_input, missatge, mida, afegit, cols);
    else if(strcmp(tipus, "dat") == 0) escriure_dat(f_input, missatge, mida, afegit, cols);
    else if(strcmp(tipus, "txt") == 0) escriure_txt(f_input, missatge, mida, afegit, cols);
    free(tipus);
}

// Escriu el contingut del missatge en un fitxer '.dat'
void escriure_dat(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *f_output = nom_foutput(f_input, afegit);
    FILE *fitxer;

    if((fitxer = fopen(f_output, "w+")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    for(int i = 0; i < mida; i++){
        if(((i+1) % cols) == 0) fprintf(fitxer, "%d\n", missatge[i]);
        else fprintf(fitxer, "%d ", missatge[i]);
    }
    free(f_output);
    fclose(fitxer);
}

// Escriu el contingut del missatge en un fitxer '.bin'
void escriure_bin(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *f_output = nom_foutput(f_input, afegit);
    FILE *fitxer;

    if((fitxer = fopen(f_output, "wb")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    fwrite(missatge, sizeof(int), mida, fitxer);
    free(f_output);
    fclose(fitxer);
}

// Escriu el contingut del missatge en un fitxer '.txt'
void escriure_txt(char *f_input, int *missatge, int mida, char *afegit, int cols){
    char *nou_input;
    const char* bin = ".bin";
    if((nou_input = (char *) malloc((strlen(f_input)+4) * sizeof(char))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    for(int i = 0; i < strlen(f_input); i++) nou_input[i] = f_input[i];
    strncat(nou_input, bin, 4);
    nou_input[strlen(f_input)+4] = '\0';

    char *f_output = nom_foutput(nou_input, afegit);
    FILE *fitxer;

    if((fitxer = fopen(f_output, "wb")) == NULL){
        fprintf(stderr, "\n[ERROR]: El fitxer %s no s'ha pogut crear...\n\n", f_output);
        exit(1);
    }
    fwrite(missatge, sizeof(int), mida, fitxer);
    free(nou_input);
    free(f_output);
    fclose(fitxer);
}

// Obté el nom que tindrà el nou fitxer en el que escriurem
char *nom_foutput(char *f_input, char *afegit){
    char *f_output;
    int check = 0;

    if((f_output = (char *) malloc((strlen(f_input)+3) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    int i, j = 0;

    for(i = 0; i < strlen(f_input); i++){
        f_output[j] = f_input[i];
        if(f_input[i] == '.' && f_input[i+1] != 'R' && check == 0){
            for(int k = 0; k < strlen(afegit); k++){
                j++;
                f_output[j] = afegit[k];
            }
            check = 1;
        }
        j++;
    }
    f_output[j] = '\0';
    return f_output;
}

// Crea el fitxer de configuració amb els valors de p i k passats per paràmetre
void configura(int p, int k){
    // Creem el fitxer o el sobreescrivim amb permisos de lectura i escriptura
    FILE *fitxer = fopen("RS-BW.cfg", "w+");
    
    // Reservem l'espai de memòria per als strings que contindran a p i k
    char *s_p;
    if((s_p = (char *) malloc((len_n(p)+1) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }
    char *s_k;
    if((s_k = (char *) malloc((len_n(k)+1) * sizeof(int))) == NULL){
        printf("[ERROR] Malloc no ha pogut reservar l'espai de memòria\n");
        exit(1);
    }

    // Transformem p i k de int a char*
    custom_itoa(p, len_n(p), s_p);
    custom_itoa(k, len_n(k), s_k);

    // Escrivim les dades al fitxer
    fprintf(fitxer, "%s%s\n", "p=", s_p);
    fprintf(fitxer, "%s%s", "k=", s_k);

    // Alliberem la memòria reservada i tanquem el fitxer
    free(s_p);
    free(s_k);
    fclose(fitxer);
}

// Funció personalitzada de itoa
void custom_itoa(int n, int len, char *nombre){
    int aux_len = len;
    while(n > 0 && len > 0){
        nombre[len-1] = n % 10 +'0';
        n = n / 10;
        len--; 
    }
    nombre[aux_len] = '\0';
}

// Retorna la longitud d'un nombre (quantitat de digits)
int len_n(int n){
    int len = 0;
    while(n != 0){
        n = n / 10;
        len++;
    }
    return len;
}


// **** FUNCIONS ARITMÈTICA **** //

// La funció retorna 1 si el nombre és primer o 0 si no ho és
int primer_test(int p){
    // Si p es divisible per qualsevol nombre entre 2 i p/2, no és primer
    for(int i = 2; i <= p/2; i++){
        if (p % i == 0){
            return 0;
        }
    }

    // Si no és divisible en el rang estudiat implica que és primer
    return 1;
}

// Si m es primer, llavors l'invers de a es a elevat a m-2 % m.
// En aquest treball ens serveix el mètode de Fermat perque m sempre és primer.
int teorema_fermat(int a, int potencia_a, int p){
    int invers = 1;
    while(potencia_a > 0){
        // si la potencia és imparell
        if(potencia_a % 2 == 1){
            invers = (invers * a) % p;
        }
        // fem la divisió entera de la potencia entre 2
        potencia_a = (int)(potencia_a / 2);
        // multipliquem la base per si mateixa
        a = (a * a) % p;
    }
    return invers;
}

int invers_a(int a, int p){
    return teorema_fermat(a, p-2, p);
}

// Retorna 0 si no es troba ordre_multiplicatiu, -1 si p no és primer i n en cas de trobar-lo
int ordre_multiplicatiu(int a, int p){
    int n = 1;
    int k = 1;
    
    // Comprovem que el mòdul sigui primer per comprovar que a i p són coprimers
    if(primer_test(p) == 0){
        printf("\n[ERROR] El mòdul ha de ser un nombre primer\n\n");
        return -1;
    }

    while (n < p){
        k = (k * a) % p;
        if(k == 1){
            return n;
        }
        n++;
    }
    return 0;
}

// Element de fp d'ordre multiplicatiu p-1
int element_primitiu(int p){
    for(int a = 1; a < p; a++){
        if(ordre_multiplicatiu(a, p) == p - 1){
            return a;
        }
    }
    printf("\nNo s'ha trobat cap element primitiu\n\n");
    return 0;
}


// **** FUNCIONS ÀLGEBRA LINEAL **** //

void llegeixvector(int p, int dim, int vect[]){
    for(int i = 0; i < dim; i++){
        printf("v(%d) = ", i + 1);
        scanf("%d", &vect[i]);
        vect[i] = vect[i] % p;
    }
    return;
}

void llegeixmatriu(int p, int files, int cols, int m[][cols]){
    for(int i = 0; i < files; i++) {
        for(int j = 0; j < cols; j++) {
            printf("a(%d, %d) = ", i+1, j+1);
            scanf("%d", &m[i][j]);
            m[i][j] = m[i][j] % p;
        }
    }
    return;
}

void imprimeixvector(int dim, int vect[]){
    for(int i = 0; i < dim; i++){
        printf("%d\t", vect[i]);
    }
    printf("\n\n");
    return;
}

void imprimeixmatriu(int files, int cols, int m[][cols]){
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    return;
}

// Multiplica un vector qualsevol per un element de Fp
void vectorxescalar(int dim, int a, int p, int vector[], int resul[]){
    for(int i = 0; i < dim; i++){
        resul[i] = (a * vector[i]) % p;
    }
    return;
}

// Multiplica una fila d'una matriu per un element de Fp
void filaxescalar(int a, int p, int fila, int cols, int m[][cols]){
    for(int i = 0; i < cols; i++){
        m[fila][i] = (a * m[fila][i]) % p;
    }
    return;
}

// Multiplica un vector por una matriu en Fp
void matriuxvector(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]){
    for(int i = 0; i < files; i++){
        for(int j = 0; j < cols; j++){
            resultat[i] += (mat[i][j] * vect[j]) % p;
        }
        resultat[i] = resultat[i] % p;
    }
    return;
}

// Suma a una fila d'una matriu un múltiple d'un altra en Fp
void suma_multiple(int multiple, int p, int fila_inici, int fila_desti, int cols, int m[][cols]){
    int aux_vector[cols];

    for(int j = 0; j < cols; j++){
        aux_vector[j] = multiple * m[fila_inici][j];
        m[fila_desti][j] = (m[fila_desti][j] + aux_vector[j]) % p;
    }
    return;
}

// Intercanvia dues files d'una matriu
void intercanvi_files(int fila_inici, int fila_desti, int cols, int m[][cols]){
    int aux_vector[cols];

    for(int j = 0; j < cols; j++){
        aux_vector[j] = m[fila_desti][j];
        m[fila_desti][j] = m[fila_inici][j];
        m[fila_inici][j] = aux_vector[j];
    }
    return;
}
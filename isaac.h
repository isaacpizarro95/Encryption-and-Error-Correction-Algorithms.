#ifndef _ISAAC
#define _ISAAC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ******* Aritmètica a Fp ******* //
int primer_test(int p);
int invers_a(int a, int p);
int ordre_multiplicatiu(int a, int p);
int element_primitiu(int p);

// ******* Àlgebra Lineal ******* //
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
void reduccio_gaussiana(int p, int files, int cols, int v_codificat[files], int v_descodificat[cols-1], int m[files][cols-1]);
int discussio_sistemes(int p, int files, int cols, int v_descodificat[cols-1], int m[files][cols]);
int vector_nul(int dim, int vect[]);
int vector_incompatible(int dim, int vect[]);

// ******* Codificació i Descodificació ******* //
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
void berlekamp_welch(int p, int files, int cols, int v_erroni[files]);
void crea_matriu_bw(int p, int files, int cols, int e, int v_erroni[files], int m_bw[files][cols]);

// ******* Manipulació arguments i fitxers ******* //
// Arguments
char *arguments(int argc, char *argv[], int *apuntador_p, int *apuntador_k, int *accio);
void assignacio_p_k(char *argument, int *p, int *k);
void check_parametres(int p, int k);

// Fitxers
char *nom_foutput(char *f_input, char *afegit);
FILE *gestio_fitxer(char *nom_fitxer, int *apuntador_r);
char *tipus_fitxer(char *nom_fitxer);
void longitud_dat(FILE *fitxer, int *apuntador_r);

// Lectura fitxers
void gestio_flectura(char *nom_fitxer, FILE *fitxer, int *missatge, int p);
void lectura_bin(FILE *fitxer, int *missatge, int p);
void lectura_dat(FILE *fitxer, int *missatge, int p);
void lectura_txt(FILE *fitxer, int *missatge, int p);

// Escriptura fitxers
void gestio_fescriptura(char *f_input, int *missatge, int mida, char *afegit);
void escriure_bin(char *f_input, int *missatge, char *afegit);
void escriure_dat(char *f_input, int *missatge, int mida, char *afegit);
void escriure_txt(char *f_input, int *missatge, int mida, char *afegit);

// Configuració
void configura(int p, int k);
void comprova_configuracio(int *p, int *k);
void llegeix_configuracio(FILE *fitxer, int *p, int *k);
int len_n(int n);
void custom_itoa(int n, int len, char *nombre);

#endif
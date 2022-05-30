#ifndef _ISAAC
#define _ISAAC

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
int vector_nul(int dim, int vect[]);
int vector_incompatible(int dim, int vect[]);
void matriuxvector(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]);
void reduccio_gaussiana(int p, int files, int cols, int v_codificat[files], int v_descodificat[cols-1], int m[files][cols-1]);
int discussio_sistemes(int p, int files, int cols, int v_descodificat[cols-1], int m[files][cols]);

// Codificació
void codificar(int p, int k, FILE *fitxer, int m[p-1][k]);
int calcul_potencia(int p, int a, int potencia);
void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]);
void codificacio(int p, int r, int k, int paraula[r/k][k], int codificat[r/k][p-1], int m[p-1][k], int missatge_codificat[]);
void dividir_missatge(int r, int k, int missatge[r], int paraules[r/k][k]);
int *realloc_missatge(int aux_r, int r, int k, int *missatge);

// Descodificació
void descodificar();
void descodificacio(int p, int r, int k, int codificat[r/k][p-1], int descodificat[r/k][k], int m[p-1][k], int missatge_descodificat[]);

// Manipulació de fitxers
int arguments(int argc, char *argv[], int *apuntador_p, int *apuntador_k, FILE *fitxer);
void assignacio_p_k(char *argument, int *p, int *k);
FILE *comprova_fitxer(char *nom, FILE * fitxer);

#endif
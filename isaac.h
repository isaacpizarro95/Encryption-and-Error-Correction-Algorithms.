#ifndef _ISAAC
#define _ISAAC

#include <stdio.h>
#include <stdlib.h>

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
void vectorxescalar(int dim, int a, int p, int vector[]);
void filaxescalar(int a, int p, int fila, int cols, int m[][cols]);
void intercanvi_files(int fila_inici, int fila_desti, int cols, int m[][cols]);
void suma_multiple(int multiple, int p, int fila_inici, int fila_desti, int cols, int m[][cols]);
void reduccio_gaussiana(int p, int files, int cols, int m[files][cols]);
int discussio_sistemes(int p, int files, int cols, int m[files][cols]);
int vector_nul(int dim, int vect[]);
int vector_incompatible(int dim, int vect[]);

// Codificació - Algorisme de Reed-Solomon
int calcul_potencia(int p, int a, int potencia);
void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]);
void codificacio(int p, int r, int k, int paraula[r/k][k], int codificat[r/k][p-1], int m[p-1][k], int missatge_codificat[]);
void dividir_missatge(int r, int k, int missatge[r], int paraules[r/k][k]);
int realloc_missatge(int r, int k, int *missatge);
void matriuxvector_codificar(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]);

// Descodificació - Algorisme de Berlekamp-Welch
void descodificacio(int p, int r, int k, int codificat[r/k][p-1], int descodificat[r/k][k], int m[p-1][k], int missatge_descodificat[]);
void matriuxvector_descodificar(int p, int files, int cols, int vect[], int resultat[], int mat[][cols]);

// Manipulació de fitxers
void check_valors(char *argument[], int *p, int *k);
void assignacio_p_k(int *nou_valor, char *argument);

#endif
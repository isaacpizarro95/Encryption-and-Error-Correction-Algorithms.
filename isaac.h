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
void matriuxvector(int dim, int p, int vect[], int mat[][dim]);
void vectorxescalar(int dim, int a, int p, int vector[]);
void filaxescalar(int a, int p, int fila, int cols, int m[][cols]);
void intercanvi_files(int fila_inici, int fila_desti, int cols, int m[][cols]);
void suma_multiple(int multiple, int p, int fila_inici, int fila_desti, int cols, int m[][cols]);
void reduccio_gaussiana(int p, int files, int cols, int m[files][cols]);
int discussio_sistemes(int p, int files, int cols, int m[files][cols]);
int vector_nul(int dim, int vect[]);
int vector_incompatible(int dim, int vect[]);

// Algorisme de Reed-Solomon
int calcul_potencia(int p, int a, int potencia);
void crea_matriu_vandermonde(int p, int files, int cols, int m[][cols]);
void codificacio(int p, int k, int paraula[k], int m[p-1][k]);

#endif
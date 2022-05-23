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
void llegeixvector(int dim, double vect[]);
void llegeixmatriu(int files, int cols, double m[][cols]);
void imprimeixvector(int dim, double vect[]);
void imprimeixmatriu(int files, int cols, double m[][cols]);
void matriuxvector(int dim, int p, double vect[], double mat[][dim]);
void vectorxescalar(int dim, int a, int p, double vector[]);
void intercanvi_files(int fila_inici, int fila_desti, int cols, double m[][cols]);
void suma_multiple(double multiple, int p, int fila_inici, int fila_desti, int cols, double m[][cols]);
void reduccio_gaussiana(int p, int files, int cols, double m_ampliada[files][cols]);
int vector_nul(int dim, double vect[]);
int vector_incompatible(int dim, double vect[]);
int discussio_sistemes(int p, int files, int cols, double m_ampliada[files][cols]);

// Algorisme de Reed-Solomon


#endif
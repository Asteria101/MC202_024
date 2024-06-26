#ifndef MATRIZESPARSA_H_
#define MATRIZESPARSA_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

typedef struct matrizesparsa {
  int    lin, col; /* vao de (0,0) a (nlin-1, ncol-1) */  
  float  valor;
  struct matrizesparsa *direita, *abaixo;
} NoMatrizEsparsa, MatrizEsparsa;

MatrizEsparsa   *LeMatrizEsparsa(char *arq);
MatrizEsparsa   *CriaMatrizEsparsa();
int              NumeroLinhasMatrizEsparsa(MatrizEsparsa *M);
int              NumeroColunasMatrizEsparsa(MatrizEsparsa *M);
bool             MatrizEsparsaVazia(MatrizEsparsa *M);
NoMatrizEsparsa *CriaNoMatrizEsparsa(int lin, int col, float valor);
bool             BuscaElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, NoMatrizEsparsa **pos);
void             InsereElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, float valor);
void             DestroiMatrizEsparsa(MatrizEsparsa **M);
void             ImprimeMatrizEsparsa(MatrizEsparsa *M); 


/* Exercicios */

float          RemoveElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col);
MatrizEsparsa *SomaMatrizesEsparsas(MatrizEsparsa *M1, MatrizEsparsa *M2);
MatrizEsparsa *MultiplicaMatrizesEsparsas(MatrizEsparsa *M1, MatrizEsparsa *M2);
MatrizEsparsa *TranspoeMatrizEsparsa(MatrizEsparsa *M);


#endif

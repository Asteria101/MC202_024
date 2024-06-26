#ifndef POLINOMIO_H_
#define POLINOMIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

typedef struct polinomio {
  float coef;
  int   expo;
  struct polinomio *prox;
} NoPolinomio, Polinomio;


Polinomio   *LePolinomio(char *arq);
NoPolinomio *CriaNoPolinomio(float coef, float expo);
bool         BuscaTermoPolinomio(Polinomio *P, int expo, NoPolinomio **termo, NoPolinomio **termo_ant);
void         InsereTermoPolinomio(Polinomio **P, float coef, int expo);
void         DestroiPolinomio(Polinomio **P);
Polinomio   *SomaPolinomios(Polinomio *P1, Polinomio *P2);
void         ImprimePolinomio(Polinomio *P); 
void         GravaPolinomio(Polinomio *P, char *nomearq); 
int          NumeroTermosPolinomio(Polinomio *P);

/* Exercicios */

NoPolinomio *RemoveTermoPolinomio(Polinomio **P, int expo);
Polinomio   *MultiplicaPolinomios(Polinomio *P1, Polinomio *P2); 

#endif

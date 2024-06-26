#ifndef _PILHA_H_
#define _PILHA_H_


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

/* Pilha em vetor linear (nao tem sentido ser circular) */

typedef struct _pilha {
  int   qtde;  // num de elementos na pilha
  int   MAX_SIZE; // tamanho maximo da pilha
  int  *val; // vetor dos valores
} Pilha;


Pilha *CriaPilha(int MAX_SIZE);
void   DestroiPilha(Pilha **Q);
char   PilhaVazia(Pilha *Q);
char   PilhaCheia(Pilha *Q);
void   Empilha(Pilha *Q, int elem); /* insere na pilha (ultima posicao) */
int    Desempilha(Pilha *Q); /* remove da pilha (ultima posicao) */
int    ConsultaPilha(Pilha *Q, int elem); /* retorna a posicao que diz
					  quando sera retornado na
					  remocao ou -1 se nao estiver
					  na pilha. */
void  ImprimePilha(Pilha *Q);


#endif

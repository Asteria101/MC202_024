#ifndef _FILA_H_
#define _FILA_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>


/* Fila em vetor circular */

typedef struct _fila {
  int   ini, fim;
  int   qtde;  // num de elementos na fila
  int   MAX_SIZE; // tamanho maximo da fila
  int  *val; // vetor dos valores
} Fila;


Fila *CriaFila(int MAX_SIZE);
void  DestroiFila(Fila **Q);
char  FilaVazia(Fila *Q);
char  FilaCheia(Fila *Q);
void  InsereFila(Fila *Q, int elem); /* insere na fila (ultima posicao) */
int   RemoveFila(Fila *Q); /* remove da fila (primeira posicao) */
int   ConsultaFila(Fila *Q, int elem); /* retorna a posicao que diz
					  quando sera retornado na
					  remocao ou -1 se nao estiver
					  na fila. */
void  ImprimeFila(Fila *Q);


#endif

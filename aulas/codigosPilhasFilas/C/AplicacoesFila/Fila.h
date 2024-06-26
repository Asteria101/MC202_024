#ifndef _FILA_H_
#define _FILA_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

/* Vamos implementar como fila circular */

typedef struct _fila {
    int ini, fim;
    int qtde; // num de elementos da fila
    int tam_max; // tamanho maximo da fila
    int *val; // vetor dos valores
} Fila;

Fila *CriaFila(int tam_max);
void  DestroiFila(Fila **Q);
bool  FilaVazia(Fila *Q);
bool  FilaCheia(Fila *Q);
bool  InsereFila(Fila *Q, int elem);
bool  RemoveFila(Fila *Q, int *elem);
bool  ConsultaFila(Fila *Q, int elem, int *pos);
void  ImprimeFila(Fila *Q);

#endif

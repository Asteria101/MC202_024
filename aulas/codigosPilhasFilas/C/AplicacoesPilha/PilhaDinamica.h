#ifndef PILHA_DINAMICA_H_
#define PILHA_DINAMICA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

typedef struct _pilha {
  char   caracter;
  float  valor;
  struct _pilha *prox;
} Pilha;

Pilha *CriaPilha(); /* Cria uma pilha vazia */
void   DestroiPilha(Pilha **pilha); /* libera a memória */
bool   PilhaVazia(Pilha *pilha); /* Verifica se a pilha está vazia */
void   EmpilhaCaracter(Pilha **pilha, char caracter); /* Insere caracter no topo da pilha */
void   EmpilhaValor(Pilha **pilha, float valor); /* Insere valor no topo da pilha */
char   DesempilhaCaracter(Pilha **pilha); /* Remove caracter do topo da pilha */
float  DesempilhaValor(Pilha **pilha); /* Remove valor do topo da pilha */

#endif

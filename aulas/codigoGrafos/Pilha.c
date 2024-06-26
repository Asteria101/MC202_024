#include "Pilha.h"

Pilha *CriaPilha(int MAX_SIZE)
{
  Pilha *Q = (Pilha *)calloc(1,sizeof(Pilha));

  Q->val      = (int *)calloc(MAX_SIZE,sizeof(int));
  Q->qtde     = 0;
  Q->MAX_SIZE = MAX_SIZE;
  
  return(Q);
}

void DestroiPilha(Pilha **Q)
{
  Pilha *aux=*Q;

  free(aux->val);
  free(aux);
  *Q = NULL;
}

char PilhaVazia(Pilha *Q)
{
  if (Q->qtde == 0)
    return(1);
  else
    return(0);
}

char PilhaCheia(Pilha *Q)
{
  if (Q->qtde == Q->MAX_SIZE)
    return(1);
  else
    return(0);
}

void Empilha(Pilha *Q, int elem)
{
  if (PilhaCheia(Q)){
    printf("Pilha cheia\n");
    exit(-1);
  }
  
  Q->val[Q->qtde]=elem;
  Q->qtde++;
}

int Desempilha(Pilha *Q)
{
  int elem;

  if (PilhaVazia(Q)){
    printf("Pilha vazia\n");
    exit(-1);
  }
  
  elem   = Q->val[Q->qtde-1]; 
  Q->qtde--;

  return(elem);
}

void ImprimePilha(Pilha *Q)
{
  int i;

  for (i=Q->qtde-1; i >= 0; i--) 
    {
      printf("%d ",Q->val[i]);
    }
  printf("\n");
}

int ConsultaPilha(Pilha *Q, int elem)
{
  int i, j;

  for (i=Q->qtde-1, j=1; i >= 0; i--,j++) 
    {
      if (Q->val[i]==elem)
	return(j);
    }

  return(-1);
}

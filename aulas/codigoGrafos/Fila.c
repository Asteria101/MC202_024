#include "Fila.h"

Fila *CriaFila(int MAX_SIZE)
{
  Fila *Q = (Fila *)calloc(1,sizeof(Fila));

  Q->val      = (int *)calloc(MAX_SIZE,sizeof(int));
  Q->qtde     = 0;
  Q->ini      = Q->fim = 0;
  Q->MAX_SIZE = MAX_SIZE;
  
  return(Q);
}

void DestroiFila(Fila **Q)
{
  Fila *aux=*Q;

  free(aux->val);
  free(aux);
  *Q = NULL;
}

char FilaVazia(Fila *Q)
{
  if (Q->qtde == 0)
    return(1);
  else
    return(0);
}

char FilaCheia(Fila *Q)
{
  if (Q->qtde == Q->MAX_SIZE)
    return(1);
  else
    return(0);
}

void InsereFila(Fila *Q, int elem)
{
  if (FilaCheia(Q)){
    printf("Fila cheia\n");
    exit(-1);
  }
  
  Q->val[Q->fim]=elem;
  Q->fim = (Q->fim+1)%Q->MAX_SIZE;
  Q->qtde++;
}

int RemoveFila(Fila *Q)
{
  int elem;

  if (FilaVazia(Q)){
    printf("Fila vazia\n");
    exit(-1);
  }
  
  elem   = Q->val[Q->ini]; 
  Q->ini = (Q->ini+1)%Q->MAX_SIZE;
  Q->qtde--;
  return(elem);
}

void ImprimeFila(Fila *Q)
{
  int i,j;

  for (i=0,j=Q->ini; i < Q->qtde; i++,j=(j+1)%Q->MAX_SIZE) 
    {
      printf("%d ",Q->val[j]);
    }
  printf("\n");
}

int ConsultaFila(Fila *Q, int elem)
{
  int i,j;

  for (i=1,j=Q->ini; i <= Q->qtde; i++,j=(j+1)%Q->MAX_SIZE) 
    {
      if (Q->val[j]==elem)
	return(i);
    }
  return(-1);
}

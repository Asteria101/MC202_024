#include "Fila.h"

Fila *CriaFila(int tam_max) {
    Fila *Q    = (Fila*) calloc(1, sizeof(Fila));
    
    Q->val     = (int*) calloc(tam_max, sizeof(int));
    Q->tam_max = tam_max;
    Q->qtde    = 0;
    Q->ini     = Q->fim = 0;

    return Q;
}

void DestroiFila(Fila **Q) {
    Fila *Qaux = *Q;
    if (Qaux != NULL){
      free(Qaux->val); // desaloca o vetor de int
      free(Qaux);
      *Q = NULL;
    }
}

/* Note que Q->ini == Q->fim ocorre em fila vazia e em fila cheia */

bool FilaVazia(Fila *Q) {
    return (Q->qtde == 0);
}

bool FilaCheia(Fila *Q) {
    return (Q->qtde == Q->tam_max);
}

bool InsereFila(Fila *Q, int elem) {
    if (FilaCheia(Q)) {
        printf("Aviso: Fila está cheia\n");
        return false; // falha na insercao
    }
    else {
        Q->val[Q->fim] = elem;
        Q->fim = (Q->fim+1) % Q->tam_max;
        Q->qtde++; 
        return true; // sucesso na insercao
    }
}

bool RemoveFila(Fila *Q, int *elem) {
    if (FilaVazia(Q)) {
        printf("Aviso: Fila está vazia\n");
        return false; // falha na remocao
    }
    else {
      *elem  = Q->val[Q->ini];
      Q->ini = (Q->ini+1) % Q->tam_max;
      Q->qtde--; 
      return true; // sucesso na remocao
    }
}


bool ConsultaFila(Fila *Q, int elem, int *pos)
{
    if (FilaVazia(Q)) {
        printf("Aviso: Fila está vazia\n");
        return false; // falha ao consultar fila
    }
    else {
      /* Note que se a fila estiver cheia, Q->ini == Q->fim */
      for (int i=0; i < Q->qtde; i++){	
	if (elem == Q->val[(i+Q->ini)%Q->tam_max]){
	  *pos = (i+Q->ini)%Q->tam_max;
	  return true; // sucesso ao consultar fila
	}
      }
    }
}

void ImprimeFila(Fila *Q)
{
  for (int i=0; i < Q->qtde; i++){	
    printf("%d ",Q->val[(i+Q->ini)%Q->tam_max]);
  }
  printf("\n");
}

#include "Heap.h"

Heap *CriaHeap(int maxsize)
{
  Heap *H = (Heap *)calloc(1,sizeof(Heap));
  
  H->maxsize = maxsize;
  H->nelems = 0;
  H->info = (int *)calloc(H->maxsize,sizeof(int));

  return(H);
}

void DestroiHeap(Heap **H)
{
  if (*H != NULL){
    free((*H)->info);
    free(*H);
    *H = NULL;
  }
}

void Troca(int *x, int *y)
{ 
  int aux;

  aux = *x;
  *x = *y;  
  *y = aux;

}

/*   O (logn) */

void DesceHeapRecursivo (Heap *H, int i)
{ 
 int maior,esq,dir;

 esq = FilhoEsquerdo(i);
 dir = FilhoDireito(i);

 if ((esq < H->nelems)&&(H->info[esq] > H->info[i]))
    maior = esq;
 else
    maior = i;

 if ((dir < H->nelems)&&(H->info[dir] > H->info[maior]))
    maior = dir;

 if (maior != i){
    Troca(&H->info[i],&H->info[maior]);
    DesceHeapRecursivo(H,maior);		
 }

}

/*   O (logn) */

void DesceHeap (Heap *H, int i)
{ 
 int maior,esq,dir;
 Boolean continua = true;

 while (continua) { 

   esq = FilhoEsquerdo(i);
   dir = FilhoDireito(i);

   if ((esq < H->nelems)&&(H->info[esq] > H->info[i]))
      maior = esq;
   else
      maior = i;

   if ((dir < H->nelems)&&(H->info[dir] > H->info[maior]))
      maior = dir;

   if (maior != i){
      Troca(&H->info[i],&H->info[maior]);
      i = maior;
   }
   else
      continua = false;
 }

}

/* O (logn) - Iterativo */

void SobeHeap(Heap *H, int i)
{
  int pai;

  pai = Pai(i);
  
  while ((pai >= 0) && (H->info[pai] < H->info[i])){
    Troca(&H->info[i],&H->info[pai]);
    i = pai;
    pai = Pai(i);
  }

}

Boolean HeapCheio(Heap *H)
{
  if (H->nelems >= H->maxsize)
    return true;
  else
    return false;
}

Boolean HeapVazio(Heap *H)
{
  if (H->nelems <= 0)
    return true;
  else
    return false;
}

void ImprimeHeap(Heap *H, int indice, int nivel)
{ 
  int i;

  if (indice < H->nelems){ 
    ImprimeHeap(H,FilhoDireito(indice),nivel+1);

    for (i=0; i < nivel; i++) 
      printf("   ");

    printf("%03d",H->info[indice]);

    for (i=0; i <= (int)log2(H->nelems)-nivel; i++) 
      printf("---");
    
    printf("\n");
    ImprimeHeap(H,FilhoEsquerdo(indice),nivel+1);
  }
}


/*   O (logn) */

void InsereHeap(Heap *H, int info) 
{ 
  if (!HeapCheio(H)) {
    H->nelems += 1;
    H->info[H->nelems-1] = info;
    SobeHeap(H,H->nelems-1);
  }

}

/*   O (logn) */

int RemoveHeap(Heap *H)
{
  int info;

  if (!HeapVazio(H)) {
    info = H->info[0];
    Troca(&(H->info[0]),&(H->info[H->nelems-1]));
    H->nelems--;
    DesceHeap(H,0);
  }

  return(info);
}

/* O(nlogn): A cada iteracao garante um heap do indice 0 ate o indice
   i, para i = 1, 2, ..., nelems-1 */

void ConstroiHeap1(Heap *H)
{
  int i;
  for(i=1;i<H->nelems;i++) { 
    SobeHeap(H,i); 
  }
}

/* O(n): a cada iteraçao garante o heap a partir do nivel i
   (direita e depois esquerda) para i = h-1 ate 0 */

void ConstroiHeap2 (Heap *H)
{ 
  int i,n;

  n = Pai(H->nelems-1);
  for (i=n; i >= 0; i--){ 
    DesceHeap(H,i); 
  }
}


/* Heapsort O(nlog(n)): Constrói o heap, caso os elementos em H não
   formem um heap binário, depois aplica as remoções de todos os
   elementos, sabendo que os elementos removidos ficam na verdade no
   vetor do heap em ordem crescente. Por fim, retoma-se o tamanho
   original do vetor. */

void HeapSort(Heap *H)
{
 int i,n = H->nelems;

 ConstroiHeap2(H);
 for (i=0; i < n; i++)
   RemoveHeap(H);
 H->nelems = n;
 
}



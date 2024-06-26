#include "Heap.h"

Heap *CriaHeap(int maxsize, int *custo)
{
  Heap *H = (Heap *)calloc(1,sizeof(Heap));
  
  H->maxsize = maxsize;
  H->nelems  = 0;
  H->no      = (int *)calloc(H->maxsize,sizeof(int));
  H->pos     = (int *)calloc(H->maxsize,sizeof(int));
  H->custo   = custo;
  
  return(H);
}

void DestroiHeap(Heap **H)
{
  if (*H != NULL){
    free((*H)->no);
    free((*H)->pos);
    free(*H);
    *H = NULL;
  }
}

void Troca(int *x, int *y)
{ 
  int aux;

  aux = *x;  *x   = *y;  *y   = aux;

}

/*   O (logn) */

void DesceHeapRecursivo (Heap *H, int no)
{ 
  int menor,esq,dir, i = H->pos[no];
 
 esq = FilhoEsquerdo(i);
 dir = FilhoDireito(i);

 if ((esq < H->nelems)&&(H->custo[H->no[esq]] < H->custo[H->no[i]]))
   menor = esq;
 else
   menor = i;

 if ((dir < H->nelems)&&(H->custo[H->no[dir]] < H->custo[H->no[menor]]))
   menor = dir;

 if (menor != i){
   Troca(&H->no[i],&H->no[menor]);
   H->pos[H->no[i]]=i;
   H->pos[H->no[menor]]=menor;
   DesceHeapRecursivo(H,menor);		
 }
}

/*   O (logn) */

void DesceHeap (Heap *H, int no)
{ 
  int     menor,esq,dir, i = H->pos[no];
 Boolean continua=true;

 while (continua) { 

   esq = FilhoEsquerdo(i);
   dir = FilhoDireito(i);

   if ((esq < H->nelems)&&(H->custo[H->no[esq]] < H->custo[H->no[i]]))
     menor = esq;
   else
     menor = i;

   if ((dir < H->nelems)&&(H->custo[H->no[dir]] < H->custo[H->no[menor]]))
     menor = dir;

   if (menor != i){
     Troca(&H->no[i],&H->no[menor]);
     H->pos[H->no[i]]=i;
     H->pos[H->no[menor]]=menor;     
     i = menor;
   }else
     continua = false;
 }

}

/* O (logn) - Iterativo */

void SobeHeap(Heap *H, int no)
{
  int pai, i = H->pos[no];

  pai = Pai(i);
  
  while ((pai >= 0) && (H->custo[H->no[pai]] > H->custo[H->no[i]])){
    Troca(&H->no[i],&H->no[pai]);
    H->pos[H->no[i]]=i;
    H->pos[H->no[pai]]=pai;     
    i   = pai;
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
    printf("%02d (%03d)",H->no[indice],H->custo[H->no[indice]]);
    for (i=0; i <= (int)log2(H->nelems)-nivel; i++) 
      printf("---");
    printf("\n");
    ImprimeHeap(H,FilhoEsquerdo(indice),nivel+1);
  }
}


/*   O (logn) */

void InsereHeap(Heap *H, int no) 
{ 
  if (!HeapCheio(H)) {
    H->nelems += 1;
    H->no[H->nelems-1] = no;
    H->pos[no]         = H->nelems-1;
    SobeHeap(H,no);
  }

}

/*   O (logn) */

int RemoveHeap(Heap *H)
{
  int no;

  if (!HeapVazio(H)) {
    no = H->no[0];
    Troca(&(H->no[0]),&(H->no[H->nelems-1]));
    H->pos[H->no[0]]=0;
    H->pos[H->no[H->nelems-1]]=H->nelems-1;     
    H->nelems--;
    DesceHeap(H,H->no[0]);
  }

  return(no);
}

/* O(nlogn): A cada iteracao garante um heap do indice 0 ate o indice
   i, para i = 1, 2, ..., nelems-1 */

void ConstroiHeap1(Heap *H)
{
  int i;
  for(i=1;i<H->nelems;i++) {
    H->pos[H->no[i]]=i;
    SobeHeap(H,H->no[i]); 
  }
}

/* O(n): a cada iteraçao garante o heap a partir do nivel i
   (direita e depois esquerda) para i = h-1 ate 0 */

void ConstroiHeap2 (Heap *H)
{ 
  int i,n;

  n = Pai(H->nelems-1);
  for (i=n; i >= 0; i--){ 
    H->pos[H->no[i]]=i;
    DesceHeap(H,H->no[i]); 
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



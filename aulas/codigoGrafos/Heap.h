#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i+1)
#define FilhoDireito(i) (2*i+2)

typedef enum{false,true} Boolean;

typedef struct _heap {
  int *no;                /* nós do grafo */
  int *pos;               /* posições dos nós no heap */
  int *custo;             /* custos dos nós */    
  int  nelems, maxsize;   /* número de elementos no heap e o tamanho do vetor */
} Heap;

Heap   *CriaHeap(int maxsize, int *custo);
void    DestroiHeap(Heap **H);
void    InsereHeap(Heap *H, int no);
int     RemoveHeap(Heap *H);
Boolean HeapCheio(Heap *H);
Boolean HeapVazio(Heap *H);
void    ImprimeHeap(Heap *H, int indice, int nivel);
void    ConstroiHeap1(Heap *H);
void    ConstroiHeap2(Heap *H);
void    HeapSort(Heap *H);
void    SobeHeap(Heap *H, int no);
void    DesceHeapRecursivo(Heap *H, int no);
void    DesceHeap(Heap *H, int no);
void    Troca(int *x, int *y);


#endif





#include "Heap.h"
#include "Heap.c"

/* gcc TestaHeap.c -o TestaHeap -lm */

Heap *LeSequencia(char *arquivo)
{
  FILE *fp = fopen(arquivo, "r");
  int   i, maxsize;
  Heap *H;

  fscanf(fp,"%d\n",&maxsize);
  H = CriaHeap(maxsize);
  for (i=0; i < H->maxsize; i++){ 
    fscanf(fp,"%d",&H->info[i]);
    H->nelems++;
  }

  fclose(fp);

  return(H);
}

void ImprimeSequencia(Heap *H)
{
  int i;

  for (i=0; i < H->nelems; i++) 
    printf("%d ",H->info[i]);
  printf("\n");

}

int main(int argc, char *argv[])
{
  Heap *H;

  if (argc != 2) {
    printf("TestHeap <sequencia.txt>\n");
    exit(-1);
  }

  H = LeSequencia(argv[1]);
  printf("Sequencia Lida\n");
  ImprimeSequencia(H);
  HeapSort(H);
  printf("Sequencia Ordenada Crescente\n");
  ImprimeSequencia(H);
  printf("A ordenacao não satisfaz a propriedade de heap máximo, mas gera um HEAP MÍNIMO\n");
  ImprimeHeap(H,0,1);
  ConstroiHeap2(H); //ConstroiHeap1(H);
  printf("Heap máximo construído\n");
  ImprimeHeap(H,0,1);

  printf("Remove %d\n",RemoveHeap(H));
  ImprimeHeap(H,0,1);
  printf("Remove %d\n",RemoveHeap(H));
  ImprimeHeap(H,0,1);
  printf("Insere 100\n");
  InsereHeap(H,100);
  ImprimeHeap(H,0,1);
  printf("Insere 0\n");
  InsereHeap(H,0);
  ImprimeHeap(H,0,1);

  DestroiHeap(&H);

  return 0;
}


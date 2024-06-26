#include "Heap.h"
#include "Heap.c"

Heap *LeSequencia(char *arquivo, int **custo)
{
  FILE *fp = fopen(arquivo, "r");
  int   i, maxsize;
  Heap *H;

  fscanf(fp,"%d\n",&maxsize);
  *custo = (int *)calloc(maxsize,sizeof(int));
  H = CriaHeap(maxsize,*custo);
  
  for (i=0; i < H->maxsize; i++){ 
    H->no[i]  = i;
    fscanf(fp,"%d",&H->custo[H->no[i]]);
    H->nelems++;
  }

  fclose(fp);

  return(H);
}

void ImprimeSequencia(Heap *H)
{
  int i;

  for (i=0; i < H->nelems; i++) 
    printf("%02d (%03d); ",H->no[i],H->custo[H->no[i]]);
  printf("\n");

}

int main(int argc, char *argv[])
{
  Heap *H;
  int  *custo;

  if (argc != 2) {
    printf("TestHeap <sequencia.txt>\n");
    exit(-1);
  }

  H = LeSequencia(argv[1],&custo);
  printf("Sequencia Lida\n");
  ImprimeSequencia(H);
  ConstroiHeap1(H);
  printf("Heap de Valor Minimo Construido\n");
  ImprimeHeap(H,0,1);
  HeapSort(H);
  printf("Sequencia Ordenada Decrescente\n");
  ImprimeSequencia(H);
  printf("A Ordenacao Destruiu o Heap de Minimo, mas Gerou um Heap de Maximo\n");
  ImprimeHeap(H,0,1);
  ConstroiHeap2(H);
  printf("Heap de Valor Minimo Reconstruido\n");
  ImprimeHeap(H,0,1);

  int no1, no2;
  printf("Remove %d\n",no1=RemoveHeap(H));
  ImprimeHeap(H,0,1);
  printf("Remove %d\n",no2=RemoveHeap(H));
  ImprimeHeap(H,0,1);
  printf("Insere %d com custo 100\n",no1);
  H->custo[no1] = 100;
  InsereHeap(H,no1);
  ImprimeHeap(H,0,1);
  printf("Insere %d com custo 0\n",no2);
  H->custo[no2] = 0;
  InsereHeap(H,no2);
  ImprimeHeap(H,0,1);

  DestroiHeap(&H);
  free(custo);

  return 0;
}


#include "mc202.h"

Grafo *MinhaFlorestaPesoMinimo(Grafo *G)
{
  Grafo *F       = (Grafo *)calloc(1,sizeof(Grafo));
  F->no          = (NoGrafo *)calloc(G->n,sizeof(NoGrafo));
  F->n           = G->n;
  int *custo     = (int *)calloc(F->n,sizeof(int));
  Heap *Q        = CriaHeap(F->n,custo);
  char *cor      = (char *)calloc(F->n,sizeof(char));

  for (int u=0; u < G->n; u++) {
    custo[u]        = INT_MAX;
    F->no[u].nome   = G->no[u].nome;
    F->no[u].adj    = NULL;
    F->no[u].m      = 0;
    F->no[u].custo  = INT_MAX;
    F->no[u].pred   = u;
    InsereHeap(Q,u);
    cor[u]          = CINZA;          
  }
  
  int rotulo=1;
  
  while(!HeapVazio(Q)){
    int u  = RemoveHeap(Q); cor[u] = PRETO;
    
    if (F->no[u].pred == u){
      F->no[u].custo  = custo[u] = 0;
      F->no[u].rotulo = rotulo; rotulo++;
    } else {
      F->no[u].m++;
      F->no[F->no[u].pred].m++;
    }
    
    printf("no %c pred %c custo %d\n",F->no[u].nome,F->no[F->no[u].pred].nome,custo[u]);

    for (int i=0; i < G->no[u].m; i++) {
      int v = G->no[u].adj[i];
      if (cor[v]!=PRETO){	
	int tmp = abs(G->no[v].valor-G->no[u].valor);
	if (tmp < custo[v]){
	  custo[v] = F->no[v].custo  = tmp;
	  F->no[v].pred   = u;
	  F->no[v].rotulo = F->no[u].rotulo;	  
	  SobeHeap(Q,v);
	}
      }
    }
  }

  free(custo);
  free(cor);
  DestroiHeap(&Q);
  
  for (int u=0; u < F->n; u++) {
    F->no[u].adj = (int *)calloc(F->no[u].m,sizeof(int));
    for (int i=0; i < F->no[u].m; i++)
      F->no[u].adj[i] = -1;
  }
  
  for (int u=0; u < F->n; u++) {
    if (F->no[u].pred != u){
      int i=0;
      while (F->no[F->no[u].pred].adj[i]!=-1) i++;
      F->no[F->no[u].pred].adj[i]=u;
      i=0;
      while (F->no[u].adj[i]!=-1) i++;
      F->no[u].adj[i]=F->no[u].pred;
    }
  }
  
  return(F);
}


int main() {

  Grafo *G = LeGrafo("grafo.txt");
  ImprimeGrafo(G);

  Grafo *F = MinhaFlorestaPesoMinimo(G);
  ImprimeGrafo(F);


  DestroiGrafo(&G);
  DestroiGrafo(&F);

  return 0;
}

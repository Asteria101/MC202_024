#include "mc202.h"

/*
gcc TestGrafo.c Grafo.c Heap.c Fila.c Pilha.c -o TestGrafo -lm
*/

int *MeuPercursoProfundidade1(Grafo *G, int inicio, int *nvisitados)
{
  Pilha *Q   = CriaPilha(G->n);
  char  *cor = (char *)calloc(G->n, sizeof(char));
  int   *percurso = (int *) calloc(G->n, sizeof(int));
  
  for (int u=0; u < G->n; u++) {
    G->no[u].custo = INT_MAX; cor[u] = BRANCO; G->no[u].pred = -1; G->no[u].rotulo = u;
    if (u == inicio){
      G->no[u].custo = 0; Empilha(Q,u); cor[u] = CINZA;
    }
  }
  (*nvisitados) = 0;
  while (!PilhaVazia(Q)){
    int u = Desempilha(Q); cor[u] = PRETO;
    percurso[*nvisitados]=u; (*nvisitados)++;
    for (int i=0; i < G->no[u].m; i++) {
      int v = G->no[u].adj[i];
      if (cor[v] != PRETO){
	G->no[v].custo  = G->no[u].custo + 1;
	G->no[v].pred   = u;
	G->no[v].rotulo = G->no[u].rotulo;
	if (cor[v] == BRANCO){
	  Empilha(Q,v); cor[v] = CINZA;
	}
      }
    }
  }
  
  free(cor);
  DestroiPilha(&Q);

  return(percurso);  
}

void BuscaRecursiva(Grafo *G, char *cor, int u, int *nvisitados, int *percurso)
{
  if (cor[u] == CINZA){
    cor[u] = PRETO;
    percurso[*nvisitados]=u; (*nvisitados)++;

    for (int i=0; i < G->no[u].m; i++) {
      int v = G->no[u].adj[i];
      if (cor[v] != PRETO){
	G->no[v].custo  = G->no[u].custo + 1;
	G->no[v].pred   = u;
	G->no[v].rotulo = G->no[u].rotulo;
	if (cor[v] == BRANCO){
	  cor[v] = CINZA;
	  BuscaRecursiva(G,cor,v,nvisitados,percurso);
	}
      }
    }
  }
}

int *MeuPercursoProfundidade2(Grafo *G, int inicio, int *nvisitados)
{
  int *percurso = (int *) calloc(G->n, sizeof(int));
  char  *cor    = (char *)calloc(G->n, sizeof(char));

  for (int u=0; u < G->n; u++) {
    G->no[u].custo = INT_MAX; cor[u] = BRANCO; G->no[u].pred = -1; G->no[u].rotulo = u;
    if (u == inicio){
      G->no[u].custo = 0; cor[u] = CINZA;
    }
  }
  
  *nvisitados = 0;
  BuscaRecursiva(G,cor,inicio,nvisitados,percurso);

  free(cor);
  return(percurso);
}

int *MeuPercursoProfundidade3(Grafo *G, int *nvisitados)
{

  /* Ficou como exercício */ 



}


void ImprimePercurso(Grafo *G, int *percurso, int nvisitados)
{
  for (int i=0; i < nvisitados; i++)
    if (G->no[percurso[i]].pred!=-1)
      printf("%c(%d,%c,%c) ",G->no[percurso[i]].nome,G->no[percurso[i]].custo,G->no[G->no[percurso[i]].pred].nome,G->no[G->no[percurso[i]].rotulo].nome);
    else
      printf("%c(%d,.,%c) ",G->no[percurso[i]].nome,G->no[percurso[i]].custo,G->no[G->no[percurso[i]].rotulo].nome);
      
  printf("\n");
}


int main() {
  Grafo *G = LeGrafo("grafo.txt"), *F;
  ImprimeGrafo(G);

  printf("Percurso em profundidade\n");
  /* int nvisitados, *percurso = MeuPercursoProfundidade1(G,4,&nvisitados);  */

  int   nvisitados = 0, *percurso = MeuPercursoProfundidade2(G,4,&nvisitados);

  /* int nvisitados, *percurso = MeuPercursoProfundidade3(G,&nvisitados); */

  
  ImprimePercurso(G,percurso,nvisitados);

  free(percurso);
  DestroiGrafo(&G);

  return 0;
}

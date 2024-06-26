#include "mc202.h"

/*
gcc TestGrafo.c Grafo.c Heap.c Fila.c Pilha.c -o TestGrafo -lm
*/

int main() {
  Grafo *G = LeGrafo("grafo.txt"), *F;
  
  ImprimeGrafo(G);

  printf("Percurso em largura\n");
  PercursoLargura(G,4);

  printf("Percurso em profundidade\n");
  PercursoProfundidade(G,4);

  printf("Arvore de caminhos minimos\n");
  ArvoreCaminhosMinimos(G,4);

  printf("Imprime grafo\n");
  ImprimeGrafo(G);

  F = FlorestaPesoMinimo(G);
  printf("Imprime floresta\n");
  ImprimeGrafo(F);
  
  DestroiGrafo(&G);
  DestroiGrafo(&F);

  return 0;
}

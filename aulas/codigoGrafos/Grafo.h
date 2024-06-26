#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <math.h>
#include "Fila.h"
#include "Pilha.h"
#include "Heap.h"

/* Codigo de cores usado para indicar a situacao de um no do grafo em
   relacao a estrutura de dados Q, que pode ser um heap, fila, ou
   pilha, dependendo do algoritmo */ 

#define BRANCO 0 /* O no nunca foi visitado (nunca entrou em Q) */
#define CINZA  1 /* O no ja foi visitado mas ainda nao foi processado */
#define PRETO  2 /* O no ja foi processado (ja saiu de Q) */

/* Implementaçao estatica: nos e arcos sao fixos para todos os algoritmos */

typedef struct _no_grafo {
  char nome; /* nome do no */
  int  valor; /* valor associado ao no para fins de computo de peso de aresta */
  int *adj, m; /* lista de adjacentes que armazena os indices deles e
		  o numero m de adjacentes */
  int pred, custo, rotulo; /* informacao extra usada por algoritmos
			      que geram subgrafos deste grafo (e.g.,
			      os percursos geram sempre uma arvore no
			      mapa de predecessores) */
} NoGrafo;

typedef struct _grafo {
  NoGrafo *no; /* lista de nos do grafo */
  int       n; /* numero de nos */ 
} Grafo;

Grafo *LeGrafo(char *nomearq);
void   DestroiGrafo(Grafo **G);
void   ImprimeGrafo(Grafo *G); 
void   PercursoLargura(Grafo *G, int inicio); /* imprime os nos a
						 partir de um no
						 inicial, seguindo o
						 percurso em
						 largura */
void   PercursoProfundidade(Grafo *G, int inicio); /* imprime os nos a
						 partir de um no
						 inicial, seguindo o
						 percurso em
						 profundidade */

void  ArvoreCaminhosMinimos(Grafo *G, int inicio); /* calcula no
						      proprio grafo a
						      subarvore de
						      caminhos de
						      custo minimo (ou
						      caminhos
						      minimos) com
						      raiz em inicio,
						      onde o custo do
						      caminho eh a
						      soma dos pesos
						      das arestas, e
						      esses sao
						      obtidos pelo
						      valor absoluto
						      da diferenca
						      entre os valores
						      dos nos. */


Grafo *FlorestaPesoMinimo(Grafo *G); /* retorna uma floresta de peso
					minimo onde cada componente do
					grafo vira uma arvore de peso
					minimo, rotulada com um numero
					distinto.  O peso de cada arco
					eh dado pela diferenca
					absoluta entre os valores de
					seus nos, como no caso da
					arvore de caminhos minimos. */



#endif

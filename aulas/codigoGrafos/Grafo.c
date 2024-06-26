#include "Grafo.h"

Grafo *LeGrafo(char *nomearq) {
	FILE *fp = fopen(nomearq,"r");

	Grafo *G = (Grafo *)calloc(1,sizeof(Grafo));

	int u, i, n;

	if (fscanf(fp,"%d\n",&n) != 1) {
		printf("Erro de leitura\n"); 
		exit(-1);
	}

	G->no = (NoGrafo *)calloc(n,sizeof(NoGrafo));
	G->n = n;

	for (u=0; u < G->n; u++) {
		G->no[u].pred = u; 
		G->no[u].custo = INT_MAX; 
		G->no[u].rotulo = u;

		if (fscanf(fp,"%c",&G->no[u].nome) != 1){ 
			printf("Erro de leitura\n"); 
			exit(-1);
		}

		if (fscanf(fp,"%d",&G->no[u].valor)!=1) { 
			printf("Erro de leitura\n"); 
			exit(-1);
		}

		if (fscanf(fp,"%d",&G->no[u].m)!=1) { 
			printf("Erro de leitura\n"); 
			exit(-1);
		}

		if (G->no[u].m > 0){

			G->no[u].adj = (int *)calloc(G->no[u].m,sizeof(int));

			for (i=0; i < G->no[u].m; i++) {
				if (fscanf(fp,"%d",&G->no[u].adj[i])!=1) {
					printf("Erro de leitura\n"); 
					exit(-1);
				}
			}

			if (fscanf(fp,"\n")!=0) { 
				printf("Erro de leitura\n"); 
				exit(-1);
			}
		}
		else {
			G->no[u].adj = NULL;
		}
	}
	
	fclose(fp);
	return(G);
}

void   DestroiGrafo(Grafo **G)
{
  Grafo *aux=*G;
  int    u;

  for (u=0; u < aux->n; u++) {
    if (aux->no[u].m > 0)
      free(aux->no[u].adj);
  }
  free(aux->no);
  free(aux);
  *G = NULL;
}

void   ImprimeGrafo(Grafo *G)
{
  int u, v, i;

  for (u=0; u < G->n; u++) {
    printf("%c (valor=%d,pred=%c,custo=%d,rotulo=%d, adjacentes={",G->no[u].nome,G->no[u].valor,G->no[G->no[u].pred].nome,G->no[u].custo,G->no[u].rotulo);
    for (i=0; i < G->no[u].m; i++) {
      v=G->no[u].adj[i];
      printf("%c,",G->no[v].nome);
    }
    printf("}\n");
  }
}

void   PercursoLargura(Grafo *G, int inicio)
{
  Fila *Q=CriaFila(G->n);  
  int   u, v, i;
  char *cor=(char *)calloc(G->n,sizeof(char));
  
  /* Inicializacao */

  for (u=0; u < G->n; u++) {
    cor[u]           = BRANCO;
    G->no[u].pred    = u; /* inicia com raiz sendo ele mesmo */
    G->no[u].rotulo  = u; /* inicia com raiz sendo ele mesmo */
    G->no[u].custo   = INT_MAX; /* comprimento do caminho para a raiz */
  }
  InsereFila(Q,inicio); cor[inicio]=CINZA; G->no[inicio].custo = 0;

  /* Propagacao */

  while (!FilaVazia(Q)){
    u      = RemoveFila(Q); cor[u]=PRETO;
    printf("%c (%c,%d,%c),",G->no[u].nome,G->no[G->no[u].pred].nome,G->no[u].custo,G->no[G->no[u].rotulo].nome);
    for (i=0; i < G->no[u].m; i++) {
      v = G->no[u].adj[i];
      if (cor[v]==BRANCO){
	G->no[v].pred   = u;
	G->no[v].custo  = G->no[u].custo + 1;
	G->no[v].rotulo = G->no[u].rotulo;
	InsereFila(Q,v); cor[v]=CINZA;
      }
    }
  }
  printf("\n");
  free(cor);
  DestroiFila(&Q);
}

void   PercursoProfundidade(Grafo *G, int inicio)
{
  Pilha *Q=CriaPilha(G->n);  
  int   u, v, i;
  char *cor=(char *)calloc(G->n,sizeof(char));
  
  /* Inicializacao */

  for (u=0; u < G->n; u++) {
    cor[u]           = BRANCO;
    G->no[u].pred    = u; /* inicia com raiz sendo ele mesmo */
    G->no[u].rotulo  = u; /* inicia com raiz sendo ele mesmo */
    G->no[u].custo   = INT_MAX; /* comprimento do caminho para a raiz */
  }
  Empilha(Q,inicio); cor[inicio]=CINZA; G->no[inicio].custo = 0;

  /* Propagacao */

  while (!PilhaVazia(Q)){
    u      = Desempilha(Q); cor[u]=PRETO;
    printf("%c (%c,%d,%c),",G->no[u].nome,G->no[G->no[u].pred].nome,G->no[u].custo,G->no[G->no[u].rotulo].nome);
    for (i=0; i < G->no[u].m; i++) {
      v = G->no[u].adj[i];
      if (cor[v]!=PRETO){	
	G->no[v].pred   = u;
	G->no[v].custo  = G->no[u].custo + 1;
	G->no[v].rotulo = G->no[u].rotulo;
	if (cor[v]==BRANCO){
	  Empilha(Q,v); cor[v]=CINZA;
	}
      }
    }
  }
  printf("\n");
  free(cor);
  DestroiPilha(&Q);
}

void  ArvoreCaminhosMinimos(Grafo *G, int inicio)
{
  int   u, v, i, tmp;
  char *cor=(char *)calloc(G->n,sizeof(char));
  int  *custo = (int *)calloc(G->n, sizeof(int));
  Heap *Q=CriaHeap(G->n,custo);  

  /* Inicializacao */

  for (u=0; u < G->n; u++) {
    cor[u]           = BRANCO;
    G->no[u].pred    = u; /* inicia com raiz sendo ele mesmo */
    G->no[u].rotulo  = u; /* inicia com raiz sendo ele mesmo */
    custo[u] = G->no[u].custo = INT_MAX; /* custo do caminho para a raiz */
  }
  custo[inicio] = G->no[inicio].custo = 0; /* custo do caminho para a raiz */  
  InsereHeap(Q,inicio); cor[inicio]=CINZA;

  /* Relaxacao e propagacao */

  while (!HeapVazio(Q)){
    u      = RemoveHeap(Q); cor[u]=PRETO;
    printf("%c (%c,%d,%c),",G->no[u].nome,G->no[G->no[u].pred].nome,G->no[u].custo,G->no[G->no[u].rotulo].nome);
    for (i=0; i < G->no[u].m; i++) {
      v = G->no[u].adj[i];
      if ((cor[v]!=PRETO)&&(G->no[u].custo < G->no[v].custo)){	
	tmp = G->no[u].custo + abs(G->no[v].valor-G->no[u].valor);
	if (tmp < G->no[v].custo){
	  custo[v] = G->no[v].custo = tmp;
	  G->no[v].pred   = u;
	  G->no[v].rotulo = G->no[u].rotulo;	  
	  if (cor[v]==BRANCO){
	    InsereHeap(Q,v); cor[v]=CINZA;
	  } else {
	    SobeHeap(Q,v);
	  }
	}
      }
    }
  }
  printf("\n");
  free(cor);
  free(custo);
  DestroiHeap(&Q);
}

Grafo *FlorestaPesoMinimo(Grafo *G)
{
  Grafo *F;
  int    u, v, i, tmp, r=1;
  char  *cor=(char *)calloc(G->n,sizeof(char));
  int   *custo = (int *)calloc(G->n, sizeof(int));
  Heap  *Q=CriaHeap(G->n,custo);  
  int   *indice;

  /* Inicializacao */

  for (u=0; u < G->n; u++) {
    custo[u] = G->no[u].custo = INT_MAX; /* custo do caminho para a raiz */
    InsereHeap(Q,u); cor[u]=CINZA;
  }
  
  /* Relaxacao e propagacao */
  
  while (!HeapVazio(Q)){
    u  = RemoveHeap(Q); cor[u]=PRETO;
    if (G->no[u].custo == INT_MAX){ /* no inicial no componente */ 
      G->no[u].pred    = u;      /* define uma raiz em u */
      G->no[u].rotulo  = r; r++; /* inicia rotulacao do componente conexo */
      custo[u] = G->no[u].custo = 0; 
    }
    printf("%c (%c,%d,%d),",G->no[u].nome,G->no[G->no[u].pred].nome,G->no[u].custo,G->no[u].rotulo);
 
    for (i=0; i < G->no[u].m; i++) {
      v = G->no[u].adj[i];
      if (cor[v]!=PRETO){	
	tmp = abs(G->no[v].valor-G->no[u].valor);
	if (tmp < G->no[v].custo){
	  custo[v] = G->no[v].custo  = tmp;
	  G->no[v].pred   = u;
	  G->no[v].rotulo = G->no[u].rotulo;	  
	  SobeHeap(Q,v);
	}
      }
    }
  }
  printf("\n");
  
  free(cor);
  free(custo);
  DestroiHeap(&Q);

  /* A Floresta eh um grafo aciclico e nao direcionado. Entao copie as
     arvores de peso minimo no grafo correspondente. */

  F      = (Grafo *)calloc(1,sizeof(Grafo));
  F->no  = (NoGrafo *)calloc(G->n,sizeof(NoGrafo));
  F->n   = G->n;
  indice = (int *)calloc(G->n,sizeof(int));

  for (u=0; u < G->n; u++) {
    F->no[u].nome   = G->no[u].nome;
    F->no[u].valor  = G->no[u].valor;
    F->no[u].pred   = G->no[u].pred; 
    F->no[u].rotulo = G->no[u].rotulo;
    F->no[u].custo  = G->no[u].custo;
    v               = G->no[u].pred; 
    if (v != u){ /* conte os adjacentes */
      F->no[u].m++; F->no[v].m++;
    }
  }    

  /* aloque memoria para os adjacentes */

  for (u=0; u < G->n; u++) {
    F->no[u].adj = (int *)calloc(F->no[u].m,sizeof(int));
  }

  /* insira os adjacentes */

  for (u=0; u < G->n; u++) {
    v = G->no[u].pred; 
    if (v != u){ 
      F->no[u].adj[indice[u]] = v; indice[u]++;
      F->no[v].adj[indice[v]] = u; indice[v]++;	  
    }
  }
  
  free(indice);

  return(F);
}

#include "mc202.h"

/*
gcc TestGrafo.c Grafo.c Heap.c Fila.c Pilha.c -o TestGrafo -lm
*/

int *MeuPercursoLargura1(Grafo *G, int inicio, int *nvisitados) {
	Fila *Q   = CriaFila(G->n);
	char *cor = (char *)calloc(G->n,sizeof(char));
	int  *percurso = (int *)calloc(G->n,sizeof(int));

	/* Linhas 1-4 */

	for (int u=0; u < G->n; u++) {
		G->no[u].custo = INT_MAX;
		cor[u] = BRANCO;
		G->no[u].pred = -1;
		G->no[u].rotulo = u;
		if (u == inicio) {
			G->no[u].custo = 0;
			InsereFila(Q,u);
			cor[u] = CINZA;
		}
	}

	*nvisitados=0; 
	while (!FilaVazia(Q)) { /* Linha 5 */
		int u  = RemoveFila(Q); /* Linha 6 */
		percurso[*nvisitados]=u; (*nvisitados)++;    
		cor[u] = PRETO;

		for (int i=0; i < G->no[u].m; i++) { /* Linha 7 */
			int v = G->no[u].adj[i];
			if (cor[v] == BRANCO) {
				/* Linha 8 */
				G->no[v].custo = G->no[u].custo + 1;
				G->no[v].pred = u;
				G->no[v].rotulo = G->no[u].rotulo;
				InsereFila(Q,v); /* Linha 9 */
				cor[v] = CINZA;
			}
		}
	}

	DestroiFila(&Q);
	free(cor);

	return(percurso);
}

int *MeuPercursoLargura2(Grafo *G, int *nvisitados) {
	int  *percurso = (int *)calloc(G->n,sizeof(int));
	Fila *Q   = CriaFila(G->n);
	char *cor = (char *)calloc(G->n,sizeof(char));


	for (int u=0; u < G->n; u++) {    
		G->no[u].custo = INT_MAX;
		cor[u] = BRANCO;
		G->no[u].pred = -1;
		G->no[u].rotulo = u;
	}
	*nvisitados = 0;

	for (int u=0; u < G->n; u++) {    
		if (G->no[u].custo==INT_MAX){ /* não foi visitado ainda */
			G->no[u].custo = 0;
			InsereFila(Q,u);
			cor[u] = CINZA;

			while (!FilaVazia(Q)) { /* Linha 5 */
				int v  = RemoveFila(Q); /* Linha 6 */
				percurso[*nvisitados]=v; (*nvisitados)++;    
				cor[v] = PRETO;

				for (int i=0; i < G->no[v].m; i++) { /* Linha 7 */
					int r = G->no[v].adj[i];
					if (cor[r] == BRANCO) {
						/* Linha 8 */
						G->no[r].custo = G->no[v].custo + 1;
						G->no[r].pred = v;
						G->no[r].rotulo = G->no[v].rotulo;
						InsereFila(Q,r); /* Linha 9 */
						cor[r] = CINZA;
					}
				}
			}
			/* Reiniciar a fila e o vetor de cor */
			Q->qtde = 0;
			Q->ini = Q->fim = 0;
			for (int u=0; u < G->n; u++) {    
				cor[u] = BRANCO;
			}
		}
	}

	DestroiFila(&Q);
	free(cor);

	return(percurso);
}


void ImprimePercurso(Grafo *G, int *percurso, int nvisitados)
{
	for (int i=0; i < nvisitados; i++) {
		if (G->no[percurso[i]].pred!=-1)
			printf("%c(%d,%c,%c) ",G->no[percurso[i]].nome,G->no[percurso[i]].custo,G->no[G->no[percurso[i]].pred].nome,G->no[G->no[percurso[i]].rotulo].nome);
		else
			printf("%c(%d,.,%c) ",G->no[percurso[i]].nome,G->no[percurso[i]].custo,G->no[G->no[percurso[i]].rotulo].nome);
	}
	printf("\n");
}


int main() {
	Grafo *G = LeGrafo("grafo.txt"), *F;
	ImprimeGrafo(G);

	printf("Percurso em largura\n");
	/* int nvisitados, *percurso = MeuPercursoLargura1(G,4,&nvisitados); */
	int nvisitados, *percurso = MeuPercursoLargura2(G,&nvisitados);

	ImprimePercurso(G,percurso,nvisitados);

	free(percurso);
	DestroiGrafo(&G);

	return 0;
}

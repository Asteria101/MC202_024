#include "mc202.h"

/*
gcc TestGrafo.c Grafo.c Heap.c Fila.c Pilha.c -o TestGrafo -lm
*/

int *MinhaArvoreCaminhosOtimos(Grafo *G, int inicio, int *nvisitados) {
	int *custo = (int *)calloc(G->n,sizeof(int));
	Heap *Q = CriaHeap(G->n,custo);
	char *cor = (char *)calloc(G->n,sizeof(char));
	int  *percurso = (int *)calloc(G->n,sizeof(int));

	/* Linhas 1-4 */

	for (int u=0; u < G->n; u++) {
		custo[u] = INT_MAX;
		cor[u] = BRANCO;

		if (u == inicio) {
			custo[u] = 0;
			InsereHeap(Q,u);
			cor[u] = CINZA;
		}
	}

	*nvisitados=0;
	
	while (!HeapVazio(Q)) { /* Linha 5 */
		int u = RemoveHeap(Q); /* Linha 6 */
		G->no[u].custo = custo[u];
		percurso[*nvisitados]=u; 
		(*nvisitados)++;    
		cor[u] = PRETO;

		for (int i=0; i < G->no[u].m; i++) { /* Linha 7 */
			int v = G->no[u].adj[i];
			if (cor[v] != PRETO) {
				/* Linha 8 */

				int tmp = custo[u] + abs(G->no[v].valor - G->no[u].valor);

				if (tmp < custo[v]) {
					custo[v]        = tmp;
					G->no[v].pred   = u;
					G->no[v].rotulo = G->no[u].rotulo;
					if (cor[v] == CINZA){ /* Linha 11 */
						SobeHeap(Q,v);
					} else { /* cor[v] == BRANCO */
						InsereHeap(Q,v); 	
						cor[v] = CINZA;
					}
				}
			}
		}
	}

	DestroiHeap(&Q);
	free(cor);
	free(custo);

	return(percurso);
}


int *MinhaFlorestaCaminhosOtimos(Grafo *G, int *nvisitados_final) {
	int *percurso_final = (int *)calloc(G->n,sizeof(int));
	int pos=0;


	for (int u=0; (u < G->n); u++) {
		if (G->no[u].custo == INT_MAX){
			int inicio = u, nvisitados;
			int *percurso = MinhaArvoreCaminhosOtimos(G, inicio, &nvisitados);
			for (int i=0; i < nvisitados; i++)
				percurso_final[pos+i] = percurso[i];
			free(percurso);
			pos += nvisitados;
		}
	}
	*nvisitados_final = pos;

	return(percurso_final);
}  


void ImprimePercurso(Grafo *G, int *percurso, int nvisitados)
{
	for (int i=0; i < nvisitados; i++)
		if (G->no[percurso[i]].pred!=percurso[i])
			printf("%c(%d,%c,%c) ",G->no[percurso[i]].nome,G->no[percurso[i]].custo,G->no[G->no[percurso[i]].pred].nome,G->no[G->no[percurso[i]].rotulo].nome);
		else
			printf("%c(%d,.,%c) ",G->no[percurso[i]].nome,G->no[percurso[i]].custo,G->no[G->no[percurso[i]].rotulo].nome);

	printf("\n");
}


int main() {
	Grafo *G = LeGrafo("grafo.txt"), *F;
	ImprimeGrafo(G);

	printf("Percurso de Dijkstra\n");
	//int nvisitados, *percurso = MinhaArvoreCaminhosOtimos(G,4,&nvisitados);
	int nvisitados, *percurso = MinhaFlorestaCaminhosOtimos(G,&nvisitados);

	ImprimePercurso(G,percurso,nvisitados);

	free(percurso);
	DestroiGrafo(&G);

	return 0;
}

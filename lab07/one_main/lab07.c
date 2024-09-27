#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i+1)
#define FilhoDireito(i) (2*i+2)

typedef enum {
    false,
    true
} Boolean;

typedef struct _no_grafo
{
    char nome;
    int  x, y;
    int rotulo;
} NoGrafo;

typedef struct _grafo
{
    NoGrafo *no;
    int n;
} Grafo;

typedef struct _heap {
    int *no;
    int *pos;
    float *distancia;
    int  nelems, maxsize;
} Heap;

typedef struct _vetor {
    int *rotulo;
    int n;
} Vetor;

Grafo *LeGrafo(char *nomearq) 
{
    FILE *fp = fopen(nomearq, "r");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    Grafo *G = (Grafo *)calloc(1, sizeof(Grafo));
    if (G == NULL) {
        printf("Erro de alocacao\n");
        exit(1);
    }

    int n;
    if (fscanf(fp, "%d\n", &n) != 1) {
        printf("Erro de leitura\n"); 
        exit(1);
    }

    G->no = (NoGrafo *)calloc(n, sizeof(NoGrafo));
    if (G->no == NULL) {
        printf("Erro de alocacao\n");
        exit(1);
    }
    G->n = n;

    for (int u = 0; u < G->n; u++) {
        G->no[u].rotulo = u;
        if (fscanf(fp, "%c", &G->no[u].nome) != 1) {
            printf("Erro de leitura\n");
            exit(1);
        }

        if (fscanf(fp, "%d", &G->no[u].x) != 1) {
            printf("Erro de leitura\n");
            exit(1);
        }

        if (fscanf(fp, "%d", &G->no[u].y) != 1) {
            printf("Erro de leitura\n");
            exit(1);
        }

        fscanf(fp, "\n");
        
    }

    fclose(fp);
    return(G);
}

float CalculaDistancia(NoGrafo *u, NoGrafo *v)
{
    return sqrtf((u->x - v->x) * (u->x - v->x) + (u->y - v->y) * (u->y - v->y));
}

float **MatrixDeAdjacencia(Grafo *G)
{
    int i, j;
    float **adj = (float **)calloc(G->n, sizeof(float *));

    for (i = 0; i < G->n; i++) {
        adj[i] = (float *)calloc(G->n, sizeof(float));
        for (j = 0; j < G->n; j++) {
            if (CalculaDistancia(&G->no[i], &G->no[j]) <= 2.0) {
                adj[i][j] = CalculaDistancia(&G->no[i], &G->no[j]);
            } else {
                adj[i][j] = 0;
            }
        }
    }

    return adj;
}

void ImprimeMatrixDeAjacencia(Grafo *G, float **adj, int n)
{
    int i, j;
    printf("Matriz de adjacencia: \n");
    for (i = -1; i < n; i++) {
        if (i != -1) {
            printf("%c", G->no[i].nome);
        }
        for (j = 0; j < n; j++) {
            if (i == -1) {
                printf("\t%c ", G->no[j].nome);
            } else {
                if (adj[i][j] != 0) {
                    printf("\t%.3f", adj[i][j]);
                } else {
                    printf("\t0");
                }
            }
        }
        printf("\n");
    }
}

Heap *CriaHeap(int maxsize, float *distancia)
{
    Heap *H = (Heap *)calloc(1, sizeof(Heap));

    H->maxsize = maxsize;
    H->nelems  = 0;
    H->no = (int *)calloc(H->maxsize, sizeof(int));
    H->pos = (int *)calloc(H->maxsize, sizeof(int));
    H->distancia = distancia;

    return(H);
}

void Troca(int *x, int *y)
{ 
    int aux = *x; *x = *y; *y = aux;
}

void DesceHeap(Heap *H, int no)
{ 
    int menor, esq, dir, i = H->pos[no];
    Boolean continua = true;

    while (continua) { 

    esq = FilhoEsquerdo(i);
    dir = FilhoDireito(i);

    if ((esq < H->nelems) && (H->distancia[H->no[esq]] < H->distancia[H->no[i]]))
        menor = esq;
    else
        menor = i;

    if ((dir < H->nelems) && (H->distancia[H->no[dir]] < H->distancia[H->no[menor]]))
        menor = dir;

    if (menor != i){
        Troca(&H->no[i], &H->no[menor]);
        H->pos[H->no[i]] = i;
        H->pos[H->no[menor]] = menor;     
        i = menor;
    } else
        continua = false;
    }
}

void SobeHeap(Heap *H, int no)
{
    int pai, i = H->pos[no];

    pai = Pai(i);

    while ((pai >= 0) && (H->distancia[H->no[pai]] > H->distancia[H->no[i]])) {
        Troca(&H->no[i], &H->no[pai]);
        H->pos[H->no[i]] = i;
        H->pos[H->no[pai]] = pai;     
        i = pai;
        pai = Pai(i);
    }
}

Boolean HeapCheio(Heap *H)
{
  if (H->nelems >= H->maxsize)
    return true;
  else
    return false;
}

Boolean HeapVazio(Heap *H)
{
  if (H->nelems <= 0)
    return true;
  else
    return false;
}

void InsereHeap(Heap *H, int no) 
{ 
    if (!HeapCheio(H)) {
        H->nelems += 1;
        H->no[H->nelems-1] = no;
        H->pos[no] = H->nelems-1;
        SobeHeap(H,no);
    }

}

int RemoveHeap(Heap *H)
{
    int no;

    if (!HeapVazio(H)) {
        no = H->no[0];
        Troca(&(H->no[0]), &(H->no[H->nelems-1]));
        H->pos[H->no[0]] = 0;
        H->pos[H->no[H->nelems-1]] = H->nelems-1;     
        H->nelems--;
        DesceHeap(H, H->no[0]);
    }

    return(no);
}

Vetor *CriaVetor(int tamanho)
{
    Vetor *V = (Vetor *)calloc(1, sizeof(Vetor));
    V->rotulo = (int *)calloc(tamanho, sizeof(int));
    V->n = 0;
    return(V);
}

void InsereVetor(Vetor *V, int rotulo)
{
    int i;
    for (i = V->n - 1; i >= 0 && V->rotulo[i] > rotulo; i--) {
        V->rotulo[i+1] = V->rotulo[i];
    }
    V->rotulo[i+1] = rotulo;
    V->n++;
}

void DestroiGrafo(Grafo **G)
{
  Grafo *aux = *G;
  free(aux->no);
  free(aux);
  *G = NULL;
}

void DestroiMatrixDeAdjacencia(float ***adj, int n)
{
    for (int i = 0; i < n; i++) {
        free((*adj)[i]);
    }
    free(*adj);
    *adj = NULL;
}

void DestroiHeap(Heap **H)
{
  if (*H != NULL){
    free((*H)->no);
    free((*H)->pos);
    free(*H);
    *H = NULL;
  }
}

void DestroiVetor(Vetor *V)
{
  free(V->rotulo);
  free(V);
  V = NULL;
}

void MinhaArvoreCaminhosOtimos(Grafo *G, int inicio, int *nvisitados, float **adj) 
{
    float *distancia = (float *)calloc(G->n, sizeof(float));
	Heap *Q = CriaHeap(G->n, distancia);
	char *cor = (char *)calloc(G->n, sizeof(char));
	int  *percurso = (int *)calloc(G->n,sizeof(int));

	/* Linhas 1-4 */

	for (int u = 0; u < G->n; u++) {
		distancia[u] = FLT_MAX;
		cor[u] = BRANCO;

		if (u == inicio) {
			distancia[u] = 0;
			InsereHeap(Q, u);
			cor[u] = CINZA;
		}
	}

	*nvisitados = 0;
	
	while (!HeapVazio(Q)) { /* Linha 5 */
		int u = RemoveHeap(Q); /* Linha 6 */
		percurso[*nvisitados] = u; 
		(*nvisitados)++;    
		cor[u] = PRETO;

        // here it changes from the original code
        for (int v = 0; v < G->n; v++) { /* Linha 7 */
            if (adj[u][v] != 0 && cor[v] != PRETO) {
                /* Linha 8 */

                float tmp = distancia[u] + adj[u][v];

                if (tmp < distancia[v]) {
                    distancia[v] = tmp;
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

    printf("Percurso [No %c]:", G->no[percurso[0]].nome);
    if (*nvisitados > 1) {
        for (int i = 1; i < *nvisitados; i++) {
            printf(" (%c %.6f) ", G->no[percurso[i]].nome, distancia[percurso[i]]);
        }
    }
    else {
        printf(" E uma ilha");
    }
    printf("\n");

    free(percurso);
	free(distancia);
}

int main(int argc, char *argv[])
{
    Grafo *G = LeGrafo(argv[1]);
    float **adj = MatrixDeAdjacencia(G);
    ImprimeMatrixDeAjacencia(G, adj, G->n);

    Vetor *vetor = CriaVetor(G->n);

    printf("Percurso mínimo: \n");
    for (int i = 0; i < G->n; i++) {
        int nvisitados;
        MinhaArvoreCaminhosOtimos(G, i, &nvisitados, adj);
        InsereVetor(vetor, G->no[i].rotulo);
    }
    
    int atual = vetor->rotulo[0];
    int componentes = 1;
    for (int i = 0; i < G->n; i++) {
        if (vetor->rotulo[i] != atual) {
            componentes++;
            atual = vetor->rotulo[i];
        }
    }
    printf("Grafo tem %d componentes\n", componentes);

    DestroiMatrixDeAdjacencia(&adj, G->n);
    DestroiGrafo(&G);
    DestroiVetor(vetor);

    return 0;
}
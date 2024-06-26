// includes

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>


// defines

/* defines to determine the node situation */
#define WHITE 0
#define GRAY  1
#define BLACK 2

/* macro for calculating distance fast */
#define Distance(x0, y0, x1, y1) sqrtf(pow((x1 - x0), 2) + pow((y1 - y0), 2))

/* macros for heap positions */
#define Father(i) ((i - 1) / 2)
#define LeftSon(i) (2 * i + 1)
#define RightSon(i) (2 * i + 2)


// structs

/* Graph structs */
typedef struct node_graph {
    char name;
    int x, y; // coordinates of the node in the plane
    int label;
    int *adj, m; // array of adjancent nodes and the size of this array
} Node_graph;

typedef struct graph {
    int n;
    Node_graph *node;
} Graph;

typedef Graph *p_graph;


/* Heap structs */
typedef struct heap {
    int n, max_size;
    int *node, *pos;
    float *distance;
} Heap;

typedef Heap *p_heap;


// functions


/* Graph functions */

/*
* Read informations of node that will compose the graph
*/
Graph *read_graph(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) exit(1);
    
    p_graph G = (p_graph)calloc(1, sizeof(Graph));
    if (G == NULL) exit(1);

    fscanf(fp, "%d\n", &G->n);

    G->node = (Node_graph *)calloc(G->n, sizeof(Node_graph));
    if (G->node == NULL) exit(1);

    for (int i = 0; i < G->n; i++) {
        G->node[i].label = i;
        G->node[i].m = 0;
        G->node[i].adj = (int *)calloc(G->n, sizeof(int));
        fscanf(fp, "%c %d %d\n", &G->node[i].name, &G->node[i].x, &G->node[i].y);
    }

    fclose(fp);
    return G;
}


/*
* Free graph memory usage
*/
void free_graph(p_graph *G) {
    p_graph aux = *G;
    for (int i = 0; i < aux->n; i++) {
        if (aux->node[i].m > 0) {
            free(aux->node[i].adj);
        }
    }
    free(aux->node);
    free(aux);
    *G = NULL;
}



/* Heap functions */

/*
* Initialize heap information
*/
p_heap create_heap(int max_size, float *distance) {
    p_heap H = (p_heap)calloc(1, sizeof(Heap));
    if (H == NULL) exit(1);

    H->max_size = max_size;
    H->n = 0;

    H->node = (int *)calloc(H->max_size, sizeof(int));
    if (H->node == NULL) exit(1);
    H->pos = (int *)calloc(H->max_size, sizeof(int));
    if (H->pos == NULL) exit(1);

    H->distance = distance;

    return H;
}


/*
* Swap two elements
*/
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


/*
* Fixdown the heap
*/
void fixdow_heap(p_heap H, int node) {
    int i = H->pos[node], smallest, left, right;

    bool keep = true;

    while (keep) {
        left = LeftSon(i);
        right = RightSon(i);
        if (((left < H->n) && (H->distance[H->node[left]] < H->distance[H->node[i]]))) {
            smallest = left;
        }

        else {
            smallest = i;
        }

        if (((right < H->n) && (H->distance[H->node[right]] < H->distance[H->node[smallest]]))) {
            smallest = right;
        }

        if (smallest != i) {
            swap(&(H->node[i]), &(H->node[smallest]));
            H->pos[H->node[i]] = i;
            H->pos[H->node[smallest]] = smallest;
            i = smallest;
        }
        else {
            keep = false;
        }
    }
}


/*
* Fixup the heap
*/
void fixup_heap(p_heap H, int node) {
    int i = H->pos[node], father = Father(i);

    while ((father >= 0 && H->distance[H->node[father]] > H->distance[H->node[i]])) {
        swap(&H->node[i], &H->node[father]);
        H->pos[H->node[i]] = i;
        H->pos[H->node[father]] = father;
        i = father;
        father = Father(i);
    }
}


/*
* Functions to verify the heap size situation
*/
bool heap_full(p_heap H) { return H->n >= H->max_size; }

bool heap_empty(p_heap H) { return H->n <= 0; }


/*
* Insert in heap
*/
void insert_heap(p_heap H, int node) {
    if (!heap_full(H)) {
        H->n++;
        H->node[H->n - 1] = node;
        H->pos[node] = H->n - 1;
        fixup_heap(H, node);
    }
}


/*
* Remove from heap
*/
int remove_heap(p_heap H) {
    int node;

    if (!heap_empty(H)) {
        node = H->node[0];
        swap(&(H->node[0]), &(H->node[H->n - 1]));

        H->pos[H->node[0]] = 0;
        H->pos[H->node[H->n - 1]] = H->n - 1;

        H->n--;
        fixdow_heap(H, H->node[0]);
    }

    return node;
}


/*
* Free heap memory usage
*/
void free_heap(p_heap *H) {
    if ((*H) != NULL) {
        free((*H)->node);
        free((*H)->pos);
        free(*H);
        *H = NULL;
    }
}



/* Adjecency Matrix functions */

/*
* Iniatilize matrix
*/
float **create_matrix(int size) {
    float **M = (float **)calloc(size, sizeof(float *));
    if (M == NULL) exit(1);

    for (int i = 0; i < size; i++) {
        M[i] = (float *)calloc(size, sizeof(float));
        if (M[i] == NULL) exit(1);
    }
    return M;
}


/*
* Load adjecency matrix with distances
*/
float **load_matrix(p_graph G) {
    float **M = create_matrix(G->n);

    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            if (i != j) {
                float dist = Distance(G->node[i].x, G->node[i].y, G->node[j].x, G->node[j].y);
                if (dist <= 2) {
                    M[i][j] = dist;
                    G->node[i].adj[G->node[i].m] = j;
                    G->node[i].m++;
                }
            }
        }
    }

    return M;
}


/*
* Print matrix
*/
void print_matrix(p_graph G, float **M, int size) {
    printf("Matriz de adjacencia: \n");
    for (int i = -1; i < size; i++) {
        if (i != -1) {
            printf("%c", G->node[i].name);
        }
        for (int j = 0; j < size; j++) {
            if (i == -1) {
                printf("\t%c ", G->node[j].name);
            }
            else {
                if (M[i][j] == 0) {
                    printf("\t0");

                }
                else {
                    printf("\t%.3f", M[i][j]);

                }
            }
        }
        printf("\n");
    }
}


/*
* Free matrix memory usage
*/
void free_matrix(float **M, int size) {
    for (int i = 0; i < size; i++) {
        free(M[i]);
    }
    free(M);
}



/*
* Runs Dijkstra's algorithm
*/
void dijkstra(p_graph G, float **adj_matrix, int source, int *visited) {
    float *distance = (float *)calloc(G->n, sizeof(float));
    char *color = (char *)calloc(G->n, sizeof(char));
    int *route = (int *)calloc(G->n, sizeof(int));
    
    p_heap Q = create_heap(G->n, distance);

    for (int i = 0; i < G->n; i++) {
        distance[i] = FLT_MAX;
        color[i] = WHITE;

        if (i == source) {
            distance[i] = 0;
            insert_heap(Q, i);
            color[i] = GRAY;
        }
    }

    *visited = 0;

    while (!heap_empty(Q)) {
        int u = remove_heap(Q);
        route[*visited] = u;
        (*visited)++;
        color[u] = BLACK;

        for (int i = 0; i < G->node[u].m; i++) {
            int v = G->node[u].adj[i];
            if (color[v] != BLACK && adj_matrix[u][v] != FLT_MAX) {
                float tmp = distance[u] + adj_matrix[u][v];


                if (tmp < distance[v]) {
                    distance[v] = tmp;
                    G->node[v].label = G->node[u].label;

                    if (color[v] == GRAY) {
                        fixup_heap(Q, v);
                    } else {
                        insert_heap(Q, v);
                        color[v] = GRAY;
                    }
                }
            }
        }
    }
    free_heap(&Q);
    free(color);

    printf("Percurso [No %c]:", G->node[route[0]].name);
    if (*visited > 1) {
        for (int i = 1; i < *visited; i++) {
            printf(" (%c %.6f) ", G->node[route[i]].name, distance[route[i]]);
        }
    }
    else {
        printf(" E uma ilha");
    }

    

    free(route);
    free(distance);
}


int main(int argc, char *argv[]) {
    p_graph G = read_graph(argv[1]);

    float **adj_matrix = load_matrix(G);
    print_matrix(G, adj_matrix, G->n);

    printf("Percurso mínimo: \n");
    for (int i = 0; i < G->n; i++) {
        int visited;
        dijkstra(G, adj_matrix, i, &visited);
        printf("\n");
    }

    int components = 1, current = G->node[0].label;
    int *analyzed = (int *)calloc(G->n, sizeof(int));
    analyzed[current] = 1;
    
    for (int i = 0; i < G->n; i++) {
        if (G->node[i].label != current && !analyzed[G->node[i].label]) {
            components++;
            current = G->node[i].label;
            analyzed[current] = 1;
        }
    }
    free(analyzed);

    printf("Grafo tem %d componentes\n", components);

    free_matrix(adj_matrix, G->n);
    free_graph(&G);

    return 0;
}
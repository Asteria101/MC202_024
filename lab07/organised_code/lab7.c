#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>


/* defines to determine the node situation */

#define WHITE 0
#define GRAY  1
#define BLACK 2


/* macros for heap positions */

#define Father(i) ((i - 1) / 2)
#define LeftSon(i) (2 * i + 1)
#define RightSon(i) (2 * i + 2)


/* macro for calculating distance fast */

#define Distance(x0, y0, x1, y1) sqrtf(pow((x1 - x0), 2) + pow((y1 - y0), 2))


/* structs */

typedef struct node_graph {
    char name;
    int x, y;
    int rotulo;
} Node_graph;

typedef struct graph {
    Node_graph *node;
    int n;
} Graph;

typedef Graph *p_graph;

typedef struct node_pos {
    int index1, index2;
    char name;
    float distance;
    int size;
} Node_pos;


typedef struct node_heap {
    int name;
    float distance;
} Node_heap;


typedef struct heap {
    int n, max_size;
    Node_heap *node;
    int *pos;
} Heap;

typedef Heap *p_heap;

void print_heap(p_heap H, int index, int level);
int find_index(p_graph G, int name);


/* basic functions */

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
        G->node[i].rotulo = i;
        fscanf(fp, "%c %d %d\n", &G->node[i].name, &G->node[i].x, &G->node[i].y);
    }

    fclose(fp);
    return G;
}


/*
* Free graph memory usage
*/
void free_graph(p_graph *G) {
    if ((*G) != NULL) {
        free((*G)->node);
        free(*G);
        *G = NULL;
    }
}


/*
* Sort and remove repeated elements from a array of integers
*/
int *sort_and_remove_repeated(int *pos, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (pos[j] > pos[j + 1]) {
                int temp = pos[j];
                pos[j] = pos[j + 1];
                pos[j + 1] = temp;
            }
        }
    }

    // Remove repeated elements
    int *unique_pos = (int *)calloc(size, sizeof(int));
    int unique_size = 0;
    for (int i = 0; i < size; i++) {
        if (i == 0 || pos[i] != pos[i - 1]) {
            unique_pos[unique_size] = pos[i];
            unique_size++;
        }
    }

    return unique_pos;
}



/* adjecency matrix functions */

/*
* Iniatilize matrix
*/
float **create_matrix(int size) {
    float **M = (float **)malloc(size * sizeof(float *));
    if (M == NULL) exit(1);

    for (int i = 0; i < size; i++) {
        M[i] = (float *)malloc(size * sizeof(float));
        if (M[i] == NULL) exit(1);

        for (int j = 0; j < size; j++) {
            M[i][j] = 0;
        }
    }
    return M;
}


/*
* Calculate distances between nodes
*/
Node_pos *node_distance(float **adj_matrix, p_graph G) {
    Node_pos *node_pos = (Node_pos *)calloc(G->n * G->n, sizeof(Node_pos));
    if (node_pos == NULL) exit(1);
    
    int k = 0;
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            if (i != j) {
                float dis = Distance(G->node[i].x, G->node[i].y, G->node[j].x, G->node[j].y);
                if (dis <= 2) {
                    node_pos[k].distance = dis;
                    node_pos[k].index1 = i;
                    node_pos[k].index2 = j;
                    k++;
                }
            }
        }
    }
    node_pos->size = k;

    return node_pos;
}


/*
* Load adjecency matrix
*/
float **load_matrix(p_graph G) {
    float **adj_matrix = create_matrix(G->n);
    Node_pos *node_pos = node_distance(adj_matrix, G);

    int k = 0;
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            if ((i == node_pos[k].index1 && j == node_pos[k].index2) && (k < node_pos->size)) {
                adj_matrix[i][j] = node_pos[k].distance;
                k++;
            }
        }
    }

    free(node_pos);

    return adj_matrix;
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



/* Heap functions */

/*
* Initialize heap information
*/
p_heap create_heap(int max_size) {
    p_heap H = (p_heap)calloc(1, sizeof(Heap));
    if (H == NULL) exit(1);

    H->max_size = max_size;
    H->n = 0;

    H->node = (Node_heap *)calloc(H->max_size, sizeof(Node_heap));
    if (H->node == NULL) exit(1);
    H->pos = (int *)calloc(H->max_size, sizeof(int));
    if (H->pos == NULL) exit(1);

    return H;
}


/*
* Swap two elements
*/
void swap(Node_heap *x, Node_heap *y) {
    Node_heap temp = *x;
    *x = *y;
    *y = temp;
}


/*
* Fixdown the heap
*/
void fixdow_heap(p_heap H, int node, p_graph G) {
    int i = H->pos[node], smallest, left = LeftSon(i), right = RightSon(i);

    if (((left < H->n) && (H->node[left].distance > H->node[i].distance)) || (H->node[left].distance == H->node[i].distance && (H->node[left].name < H->node[i].name))) {
        smallest = left;
    }

    else {
        smallest = i;
    }

    if ((right < H->n && H->node[right].distance > H->node[smallest].distance) || (H->node[right].distance == H->node[smallest].distance && (H->node[right].name < H->node[smallest].name))) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&H->node[i], &H->node[smallest]);
        int u = find_index(G, H->node[i].name), v = find_index(G, H->node[smallest].name);
        H->pos[u] = i;
        H->pos[v] = smallest;
        fixdow_heap(H, smallest, G);
    }
}


/*
* Fixup the heap
*/
void fixup_heap(p_heap H, int node, p_graph G) {
    int i = H->pos[node], father = Father(i);

    if (father >= 0 && H->node[father].distance > H->node[i].distance) {
        swap(&H->node[i], &H->node[father]);
        int u = find_index(G, H->node[i].name), v = find_index(G, H->node[father].name);
        H->pos[u] = i;
        H->pos[v] = father;
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
void insert_heap(p_heap H, Node_heap node, p_graph G) {
    if (!heap_full(H)) {
        H->n++;
        H->node[H->n - 1] = node;
        fixup_heap(H, H->n - 1, G);
    }
}


/*
* Remove from heap
*/
Node_heap remove_heap(p_heap H, p_graph G) {
    Node_heap node;

    if (!heap_empty(H)) {
        node = H->node[0];
        swap(&(H->node[0]), &(H->node[H->n - 1]));

        H->pos[H->node[0].name] = 0;

        H->n--;
        fixdow_heap(H, 0, G);
    }

    return node;
}


/*
* Build maximum heap
*/
void build_heap_max(p_heap H, p_graph G) {
    int n = Father(H->n - 1);
    for(int i = n; i >= 0; i--) { 
        fixdow_heap(H, i, G); 
    }
}


/*
* Sort heap
*/
/*void heap_sort(Heap *H) {
    int i, n = H->n;

    build_heap_max(H);
    for (i = 0; i < n; i++)
        remove_heap(H);
    H->n = n;

}*/


/*
* Sort heap considering the equidistant nodes
*/
/*void sort_heap(p_heap H) {
    int i = 1, k = 0, *pos = (int *)calloc(H->n, sizeof(int));
    while (i < H->n) {
        int j = i;
        if (j > 0 && H->node[j].distance == H->node[j-1].distance) {
            if (H->node[j].name < H->node[j-1].name || H->node[j].name == H->node[j-2].name) {
                swap(&H->node[j], &H->node[j-1]);
            }
            pos[k] = H->node[j-2].name;
            k++;
            pos[k] = H->node[j-1].name;
            k++;
            pos[k] = H->node[j].name;
            k++;
            j--;
        }
        i++;
    }

    int *names_pos = sort_and_remove_repeated(pos, k);


    free(pos);
    free(names_pos);
}*/

/*
* Print minimum route
*/
void print_sequence(p_heap H) {
    printf("Percurso [No %c]:", H->node[0].name);
    for (int i = 1; i < H->n; i++) {
        printf(" (%c %.6f) ", H->node[i].name, H->node[i].distance);
    }
    printf("\n");
}


/*
* Print heap as a tree
*/
void print_heap(p_heap H, int index, int level) {
    int i;
    if (index < H->n) {
        print_heap(H, RightSon(index), level + 1);

        for (i = 0; i < level; i++) {
            printf("         ");
        }

        printf("[%c](%.6f)", H->node[index].name, H->node[index].distance);

        for (i = 0; i <= (int)log2(H->n) - level; i++) {
            printf("---");
        }

        printf("\n");
        print_heap(H, LeftSon(index), level + 1);
    }
}


/*
* Free heap memory usage
*/
void free_heap(p_heap *H) {
    if ((*H) != NULL) {
        free((*H)->node);
        free(*H);
        *H = NULL;
    }
}



/* Dijkstra's Algorithm */

/*
* Utility function to find the vertex with minimum distance value
*/
int find_index(p_graph G, int name) {
    for (int i = 0; i < G->n; i++) {
        if (name == G->node[i].name) {
            return i;
        }
    }
    return 0;
}


/*
* Runs Dijkstra's algorithm
*/
void dijkstra(p_graph G, float **adj_matrix, int source) {
    float dist[G->n];
    int size_dist = 1;
    char shortest_path_tree[G->n];

    p_heap Q = create_heap(G->n);

    for (int i = 0; i < G->n; i++) {
        dist[i] = FLT_MAX;
        shortest_path_tree[i] = WHITE;

        if (i == source) {
            dist[i] = 0;
            insert_heap(Q, (Node_heap){G->node[i].name, dist[i]}, G);
            shortest_path_tree[i] = GRAY;
        }
    }

    while (!heap_empty(Q)) {
        Node_heap node = remove_heap(Q, G);
        int u = find_index(G, node.name);
        shortest_path_tree[u] = BLACK;


        for (int i = 0; i < G->n; i++) {
            if (shortest_path_tree[i] != BLACK && adj_matrix[u][i] != 0 && dist[u] != FLT_MAX && dist[u] + adj_matrix[u][i] < dist[i]) {
                float tmp = dist[u] + adj_matrix[u][i];
                size_dist++;

                if (tmp < dist[i]) {
                    dist[i] = tmp;
                    Q->node[i].distance = dist[i];
                    G->node[i].rotulo = G->node[u].rotulo;
                    // adicionar em vetor circular com os valores ordenados pelo valor da distância e o se for igual pelo indice em G

                    if (shortest_path_tree[i] == GRAY) {
                        fixup_heap(Q, i, G);
                    }
                    else {
                        insert_heap(Q, (Node_heap){G->node[i].name, dist[i]}, G);
                        shortest_path_tree[i] = GRAY;
                    }
            printf("dist[%c] = %.6f\n", G->node[i].name, tmp);
                }
            }
        }
    }

    free_heap(&Q);
}


int main(int argc, char *argv[]) {
    p_graph G = read_graph(argv[1]);

    float **adj_matrix = load_matrix(G);
    print_matrix(G, adj_matrix, G->n);

    printf("Percurso mínimo: \n");
    //dijkstra(G, adj_matrix, 3);
    for (int i = 0; i < G->n; i++) {
        dijkstra(G, adj_matrix, i);
        printf("\n");
    }


    free_matrix(adj_matrix, G->n);

    return 0;
}
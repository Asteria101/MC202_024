#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>


/* defines to determine the node situation */

#define WHITE 0
#define GRAY 1
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
        fscanf(fp, "%c %d %d\n", &G->node[i].name, &G->node[i].x, &G->node[i].y);
    }

    fclose(fp);
    return G;
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



/* Dijkstra's Algorithm */

/*
* Utility function to find the vertex with minimum distance value
*/
int min_distance(p_graph G, float dist[], bool sptSet[]) {
    float min = FLT_MAX;
    int min_index;

    for (int i = 0; i < G->n; i++) {
        if (sptSet[i] == false && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}


/*
* Prints the routes
*/
void print_route(p_graph G, Node_pos *node_pos, float *dist, int source) {
    printf("Percurso [No %c]:", G->node[source].name);
    int n = node_pos[0].size;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (node_pos[j].distance != 0 && dist[i] == node_pos[j].distance) {
                printf(" (%c %.6f) ", node_pos[j].name, node_pos[j].distance);
                node_pos[j].distance = 0;
            }
        }
    }
    printf("\n");
}


/*
* Sorts a float array in ascending order
*/
float *sort_float_array(float arr[], int size, int size_dist) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    float *temp = calloc(size_dist, sizeof(float));
    for (int i = 0; i < size_dist; i++) {
        temp[i] = arr[i];
    }

    return temp;
}


/*
* Runs Dijkstra's algorithm
*/
void dijkstra(p_graph G, float **adj_matrix, int source) {
    float dist[G->n];
    int size_dist = 1;
    bool shortest_path_tree[G->n];

    for (int i = 0; i < G->n; i++) {
        dist[i] = FLT_MAX;
        shortest_path_tree[i] = false;
    }

    dist[source] = 0;

    for (int i = 0; i < G->n - 1; i++) {
        int u = min_distance(G, dist, shortest_path_tree);
        shortest_path_tree[u] = true;

        for (int j = 0; j < G->n; j++) {
            
            if (!shortest_path_tree[j] && adj_matrix[u][j] != 0 && dist[u] != FLT_MAX && dist[u] + adj_matrix[u][j] < dist[j]) {
                dist[j] = dist[u] + adj_matrix[u][j];
                size_dist++;
            }
        }
    }

    Node_pos *node_pos = calloc(size_dist, sizeof(Node_pos));
    if (node_pos == NULL) exit(1);
    int k = 0;
    for (int i = 0; i < G->n; i++) {
        if (i != source && dist[i] != FLT_MAX) {
            if (k != size_dist) {
                node_pos[k].distance = dist[i];
                node_pos[k].name = G->node[i].name;
                node_pos[k].size = size_dist; 
                k++;
            }
        }
    }

    float *dist_sorted = sort_float_array(dist, G->n, size_dist);

    if (size_dist > 1) {
        print_route(G, node_pos, dist_sorted, source);
    }
    else {
        printf("Percurso [No %c]: E uma ilha\n", G->node[source].name);
    }

   free(node_pos);
   free(dist_sorted);
}



int main(int argc, char *argv[]) {
    p_graph G = read_graph(argv[1]);

    float **adj_matrix = load_matrix(G);
    print_matrix(G, adj_matrix, G->n);

    printf("Percurso mínimo: \n");
    //dijkstra(G, adj_matrix, 3);
    for (int i = 0; i < G->n; i++) {
        dijkstra(G, adj_matrix, i);
    }

    free_matrix(adj_matrix, G->n);

    return 0;
}
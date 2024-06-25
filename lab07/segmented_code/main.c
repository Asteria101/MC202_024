#include "heap.h"
#include "adj_matrix.h"


/*
* Runs Dijkstra's algorithm
*/
void minimum_spanning_tree(p_graph G, float **adj_matrix, int source, int *visited) {
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
        minimum_spanning_tree(G, adj_matrix, i, &visited);
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

    return 0;
}
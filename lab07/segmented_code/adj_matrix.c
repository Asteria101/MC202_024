#include "adj_matrix.h"

float **create_matrix(int size) {
    float **M = (float **)calloc(size, sizeof(float *));
    if (M == NULL) exit(1);

    for (int i = 0; i < size; i++) {
        M[i] = (float *)calloc(size, sizeof(float));
        if (M[i] == NULL) exit(1);
    }
    return M;
}


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
                    G->node[i].adj = (int *)realloc(G->node[i].adj, G->node[i].m * sizeof(int));
                }
            }
        }
    }

    return M;
}


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


void free_matrix(float **M, int size) {
    for (int i = 0; i < size; i++) {
        free(M[i]);
    }
    free(M);
}

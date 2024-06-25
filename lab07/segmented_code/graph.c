#include "graph.h"

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
        G->node[i].adj = (int *)calloc(1, sizeof(int));
        fscanf(fp, "%c %d %d\n", &G->node[i].name, &G->node[i].x, &G->node[i].y);
    }

    fclose(fp);
    return G;
}

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
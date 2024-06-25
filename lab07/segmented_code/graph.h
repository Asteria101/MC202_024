#ifndef GRAPH_H
#define GRAPH_H

#include "includes.h"


/* defines to determine the node situation */
#define WHITE 0
#define GRAY  1
#define BLACK 2


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


/*
* Read informations of node that will compose the graph
*/
Graph *read_graph(char *filename);

/*
* Free graph memory usage
*/
void free_graph(p_graph *G);


#endif
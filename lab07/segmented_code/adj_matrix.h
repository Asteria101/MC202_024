#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include "graph.h"

/* macro for calculating distance fast */
#define Distance(x0, y0, x1, y1) sqrtf(pow((x1 - x0), 2) + pow((y1 - y0), 2))

/* adjecency matrix functions */

/*
* Iniatilize matrix
*/
float **create_matrix(int size);


/*
* Load adjecency matrix with distances
*/
float **load_matrix(p_graph G);


/*
* Print matrix
*/
void print_matrix(p_graph G, float **M, int size);


/*
* Free matrix memory usage
*/
void free_matrix(float **M, int size);

#endif
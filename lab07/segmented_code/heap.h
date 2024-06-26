#ifndef HEAP_H
#define HEAP_H

#include "graph.h"


/* macros for heap positions */
#define Father(i) ((i - 1) / 2)
#define LeftSon(i) (2 * i + 1)
#define RightSon(i) (2 * i + 2)


typedef struct heap {
    int n, max_size;
    int *node, *pos;
    float *distance;
} Heap;

typedef Heap *p_heap;

/* Heap functions */

/*
* Initialize heap information
*/
p_heap create_heap(int max_size, float *distance);

/*
* Swap two elements
*/
void swap(int *x, int *y);

/*
* Fixdown the heap
*/
void fixdow_heap(p_heap H, int node);

/*
* Fixup the heap
*/
void fixup_heap(p_heap H, int node);

/*
* Functions to verify the heap size situation
*/
bool heap_full(p_heap H);
bool heap_empty(p_heap H);

/*
* Insert in heap
*/
void insert_heap(p_heap H, int node);

/*
* Remove from heap
*/
int remove_heap(p_heap H);

/*
* Free heap memory usage
*/
void free_heap(p_heap *H);

#endif
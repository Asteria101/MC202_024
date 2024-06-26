#include "heap.h"

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


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


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


bool heap_full(p_heap H) { return H->n >= H->max_size; }
bool heap_empty(p_heap H) { return H->n <= 0; }


void insert_heap(p_heap H, int node) {
    if (!heap_full(H)) {
        H->n++;
        H->node[H->n - 1] = node;
        H->pos[node] = H->n - 1;
        fixup_heap(H, node);
    }
}


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


void free_heap(p_heap *H) {
    if ((*H) != NULL) {
        free((*H)->node);
        free(*H);
        *H = NULL;
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h> 

#define MAX_SIZE_IP 16

#define Father(i) ((i - 1) / 2)
#define LeftSon(i) (2 * i + 1)
#define RightSon(i) (2 * i + 2)


struct info {
    char ip[MAX_SIZE_IP];
    int priority;
    double latency;
};

typedef struct heap {
    int n;
    int max_size;
    struct info *data;
} Heap;

typedef Heap *p_heap;


/* Basic functions */

p_heap create_heap(int max_size) {
    p_heap H = (p_heap)calloc(1, sizeof(Heap));

    H->max_size = max_size;
    H->n = 0;

    H->data = (struct info *)calloc(H->max_size, sizeof(struct info));

    return H;
}


p_heap read(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) exit(1);

    int total_ips;
    fscanf(fp, "%d\n", &total_ips);

    p_heap H = create_heap(total_ips);

    for (int i = 0; i < H->max_size; i++) {
        char ip[MAX_SIZE_IP];
        int priority = 0;
        float latency = 0.5;
        fscanf(fp, "%s %d %f\n", ip, &priority, &latency);
        H->n++;
        strcpy(H->data[H->n - 1].ip, ip);
        H->data[H->n - 1].priority = priority;
        H->data[H->n - 1].latency = latency;
    }

    fclose(fp);

    return H;
}


int is_heap_empty(p_heap H) {
    return (H->n <= 0);
}


void destroy_heap(p_heap *H) {
    if ((*H) != NULL) {
        free((*H)->data);
        free(*H);
        *H = NULL;
    }
}


/* Printing functions */

void print_sequence(p_heap H) {
    for (int i = 0; i < H->n; i++) {
        printf("%s %d %.2lf\n", H->data[i].ip, H->data[i].priority, H->data[i].latency);
    }
    printf("\n");
}


void print_heap(p_heap H, int index, int level) {
    int i;
    if (index < H->n) {
        print_heap(H, RightSon(index), level + 1);

        for (i = 0; i < level; i++) {
            printf("         ");
        }

        printf("[%d](%s)[%.2lf]", H->data[index].priority, H->data[index].ip, H->data[index].latency);

        for (i = 0; i <= (int)log2(H->n) - level; i++) {
            printf("---");
        }

        printf("\n");
        print_heap(H, LeftSon(index), level + 1);
    }
}


/* Manipulations with the heap */

void swap(struct info *x, struct info *y) {
    struct info aux = *x;
    *x = *y;
    *y = aux;
}


void fixdown_heap(p_heap H, int i) {
    int largest = i, left = LeftSon(i), right = RightSon(i);

   if (((left < H->n) && (H->data[left].priority > H->data[largest].priority)) || ((H->data[left].priority == H->data[largest].priority) && (H->data[left].latency < H->data[largest].latency))) {
        largest = left;
    }

    if (((right < H->n) && (H->data[right].priority > H->data[largest].priority)) || ((H->data[right].priority == H->data[largest].priority) &&  (H->data[right].latency < H->data[largest].latency))) {
        largest = right;
    }

    if (largest != i) {
        swap(&(H->data[i]), &(H->data[largest]));
        fixdown_heap(H, largest);
    }
}


struct info remove_heap(p_heap H) {
    struct info data;

    if (!is_heap_empty(H)) {
        data = H->data[0];
        swap(&(H->data[0]), &(H->data[H->n - 1]));
        H->n--;
        fixdown_heap(H, 0);
    }

    return data;
}


void build_heap(p_heap H) {
    int n = Father(H->n - 1);
    for (int i = n; i >= 0; i--) {
        fixdown_heap(H, i);
    }
}


int main(int argc, char *argv[]) {
    p_heap H = read(argv[1]);

    printf("1) Sequencia Lida\n");
    print_sequence(H);

    printf("2) Heap maximo construido\nImprimindo heap\n");
    build_heap(H);
    print_heap(H, 0, 1);

    printf("3) Removendo elementos do heap por ordem de prioridade e restricao de latencia\n");
    while (!is_heap_empty(H)) {
        struct info data = remove_heap(H);
        if (H->n > 0) {
            printf("Removido elemento de prioridade %d com valor de latencia %.6f e valor de IP %s\n", data.priority, data.latency, data.ip);
            printf("Imprimindo heap\n");
        }
        else {   
            printf("Removido elemento de prioridade %d com valor de latencia %.6f e valor de IP %s", data.priority, data.latency, data.ip);
        }
        print_heap(H, 0, 1);
    }

    destroy_heap(&H);
    return 0;
}
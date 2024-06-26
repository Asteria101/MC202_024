#include <stdio.h>
#include <stdlib.h>

struct fila {
    int ini, fim;
    int size; // num de elementos da fila
    int max_size; // tamanho maximo da fila
    int *dados; // vetor de valores
};

typedef struct fila *p_fila;


p_fila cria_fila(int tam_max) {
    p_fila F = calloc(1, sizeof(struct fila));
    F->max_size = tam_max;
    F->dados = calloc(tam_max, sizeof(int));
    F->size = 0;
    F->ini = F->fim = 0;
    return F;
}


int fila_vazia(p_fila F) {
    return (F->size == 0);
}


int fila_cheia(p_fila F) {
    return (F->size == F->max_size);
}


void insere_fila(p_fila F, int elem){
    if (!fila_cheia(F)) {
        F->dados[F->fim] = elem;
        F->fim = (F->fim + 1) % F->max_size;
        F->size++;
    }
    
}


void remove_fila(p_fila F, int *elem) {
    if (!fila_vazia(F)) {
        *elem = F->dados[F->ini];
        F->ini = (F->ini + 1) % F->max_size;
        F->size--;
    }
}


void imprime_fila(p_fila F) {
    for (int i = 0; i < F->size; i++) {
        printf("%d ", F->dados[(i + F->ini) % F->max_size]);
    }
    printf("\n");
}


int main() {
    p_fila F = cria_fila(6);
    int elem;

    for (int i = 0; i < 7; i++) {
        insere_fila(F, i);
    }
    imprime_fila(F);

    remove_fila(F, &elem);
    imprime_fila(F);

    return 0;
}
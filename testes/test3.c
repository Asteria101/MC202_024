#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
}No, Lista;

typedef struct no_d {
    int info;
    struct no_d *prox, *ant;
}No_d, Lista_d;


/*
* Lista Simples
*/
No *cria_no(int n) {
    No *p = malloc(sizeof(No));
    p->info = n;
    p->prox = NULL;
    return p;
}

void insere_fim(No **head, int n) {
    No *p = cria_no(n);

    if ((*head) == NULL) (*head) = p;

    else {
        No *current = *head;
        while (current->prox != NULL) {
            current = current->prox;
        }
        current->prox = p;
    }   
}

void imprime(No *head) {
    while (head != NULL) {
        printf("%d", head->info);
        head = head->prox;

        if (head != NULL) printf(", ");
    }
    printf("\n");
}


/*
* Lista Dupla
*/
No_d *cria_no_d(int n) {
    No_d *q = malloc(sizeof(No_d));
    q->info = n;
    q->ant = NULL;
    q->prox = NULL;
    return q;
}

void insere_fim_d(No_d **head, int n) {
    No_d *q = cria_no_d(n);

    if (*head == NULL) *head = q;

    else {
        No_d *r = *head;
        while (r->prox != NULL) r = r->prox;

        q->prox = NULL;
        q->ant = r;
        r->prox = q;
    }
}

void imprime_d(No_d *head) {
    while (head != NULL) {
        printf("%d", head->info);
        if (head->prox != NULL) printf(", ");
        head = head->prox;
    }
    printf("\n");
}


/*
* Questão
*/
void copia_em_dupla(Lista *L, Lista_d **Ld) {
    No_d *aux;

    if (L != NULL) {
        aux = calloc(1, sizeof(No_d));
        aux->info = L->info;
        aux->ant = (*Ld);
        aux->prox = NULL;

        if ((*Ld) == NULL) (*Ld) = aux;
        else (*Ld)->prox = aux;

        copia_em_dupla(L->prox, &aux);
    }
}

int main() {
    No *Ls = NULL;
    No_d *Ld = NULL;

    for (int i = 0; i < 6; i++) insere_fim(&Ls, i);

    copia_em_dupla(Ls, &Ld);
    imprime_d(Ld);

    return 0;
}
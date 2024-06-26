#include "PilhaEstatica.h"

/* gcc TestaPilha.c PilhaEstatica.c -o TestaPilha */

int main() {
    Pilha *Q = CriaPilha(5);
    int   ndes, elem;

    Desempilha(Q,&elem);
    printf("Empilha 1\n");
    Empilha(Q, 1);
    ImprimePilha(Q);
    printf("Empilha 2\n");
    Empilha(Q, 2);
    ImprimePilha(Q);
    if (Desempilha(Q,&elem))
      printf("Desempilhou %d\n",elem);
    ImprimePilha(Q);
    printf("Empilha 3\n");
    Empilha(Q, 3);
    ImprimePilha(Q);
    printf("Empilha 4\n");
    Empilha(Q, 4);
    ImprimePilha(Q);
    if (Desempilha(Q,&elem))
      printf("Desempilhou %d\n",elem);
    printf("Empilha 5\n");
    Empilha(Q, 5);
    ImprimePilha(Q);
    printf("Empilha 6\n");
    Empilha(Q, 6);
    ImprimePilha(Q);
    if (ConsultaPilha(Q, 3, &ndes))
      printf("O elemento 3 será desempilhado após %d elementos\n",ndes);
    DestroiPilha(&Q);

    return 0;
}

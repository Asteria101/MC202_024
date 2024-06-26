#include "Pilha.h"
#include "Pilha.c"


int main() {
    Pilha *Q = CriaPilha(5);
    int   pos, elem;

    printf("Empilha 1\n");
    Empilha(Q, 1);
    ImprimePilha(Q);
    printf("Empilha 2\n");
    Empilha(Q, 2);
    ImprimePilha(Q);
    printf("Desempilha %d\n",Desempilha(Q));
    ImprimePilha(Q);
    printf("Empilha 3\n");
    Empilha(Q, 3);
    ImprimePilha(Q);
    printf("Empilha 4\n");
    Empilha(Q, 4);
    ImprimePilha(Q);
    printf("Desempilha %d\n",Desempilha(Q));
    printf("Empilha 5\n");
    Empilha(Q, 5);
    ImprimePilha(Q);
    printf("Empilha 6\n");
    Empilha(Q, 6);
    ImprimePilha(Q);
    elem=5;
    pos=ConsultaPilha(Q, elem);
    if (pos != -1)
      printf("O elemento %d na posicao %d para sair da pilha \n",elem,pos);
    DestroiPilha(&Q);

    return 0;
}

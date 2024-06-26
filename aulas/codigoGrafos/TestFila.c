#include "Fila.h"
#include "Fila.c"


int main() {
    Fila *Q = CriaFila(5);
    int   pos, elem;

    printf("Insere 1\n");
    InsereFila(Q, 1);
    ImprimeFila(Q);
    printf("Insere 2\n");
    InsereFila(Q, 2);
    ImprimeFila(Q);
    printf("Remove %d\n",RemoveFila(Q));
    ImprimeFila(Q);
    printf("Insere 3\n");
    InsereFila(Q, 3);
    ImprimeFila(Q);
    printf("Insere 4\n");
    InsereFila(Q, 4);
    ImprimeFila(Q);
    printf("Remove %d\n",RemoveFila(Q));
    printf("Insere 5\n");
    InsereFila(Q, 5);
    ImprimeFila(Q);
    printf("Insere 6\n");
    InsereFila(Q, 6);
    ImprimeFila(Q);
    elem=5;
    pos=ConsultaFila(Q, elem);
    if (pos != -1)
      printf("O elemento %d na posicao %d para sair da fila \n",elem,pos);
    DestroiFila(&Q);

    return 0;
}

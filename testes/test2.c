#include <stdio.h>
#include <stdlib.h>

typedef struct _pessoa {
    //char nome[100];
    int idade;
} Pessoa;

typedef struct _amigos {
    Pessoa *p;
    int npessoas;
} Amigo;

Pessoa AmigoMaisVelho(Amigo *a, int inicio, int fim) {
    if (inicio == fim) {
        return a->p[inicio];
    }

    else {
        int meio = (inicio + fim) / 2;
        Pessoa q = AmigoMaisVelho(a, inicio, meio);
        Pessoa r = AmigoMaisVelho(a, meio+1, fim);

        if (q.idade > r.idade) {
            return q;
        }
        else {
            return r;
        }
    }
}

int main() {
    Amigo *a = calloc(1, sizeof(Amigo));
    a->p = calloc(5, sizeof(Pessoa));

    for (int i = 0; i < 5; i++) {
        scanf("%d", &a->p[i].idade);
    }

    printf("%d\n", AmigoMaisVelho(a, 0, 4).idade);

    free(a->p);
    free(a);

    return 0;
}
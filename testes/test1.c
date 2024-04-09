#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

typedef enum {
    false, true
}bool;

typedef struct _ponto {
    float x, y;
} Ponto, Vetor;

typedef struct _triangulo {
    Ponto P[3];
} Triangulo;


bool Tri (Triangulo T) {
    for (int i = 0; i < 3; i++) {
        Vetor V[2];
        V[0].x = T.P[(i+1) % 3].x-T.P[i].x;
        V[0].y = T.P[(i+1) % 3].y-T.P[i].y;

        V[1].x = T.P[(i+2) % 3].x-T.P[i].x;
        V[1].y = T.P[(i+2) % 3].y-T.P[i].y;

        for (int j = 0; j < 2; j++) {
            float m = sqrt(V[j].x * V[j].x + V[j].y * V[j].y);
            if (m > 0.0001) {
                V[j].x /= m;
                V[j].y /= m;
            }
        }

        float angulo = 180.0 * (acos((V[0].x * V[1].x) + (V[0].y * V[1].y))) / M_PI;

        if ((angulo < 90.0001) && (angulo > 89.9999)) {
            return (true);
        }
    }
    return (false);
}

int main() {
    Triangulo T;
    T.P[0].x = 0;
    T.P[0].y = 0;

    T.P[1].x = 4;
    T.P[1].y = 0;

    T.P[2].x = 4;
    T.P[2].y = 3;

    if (Tri(T) == true) {
        printf("Boa!\n");
    }
    else {
        printf("Se fudeu!\n");
    }


    return 0;
}
#include "Polinomio.h"

/* gcc SomaPolinomios.c Polinomio.c -o SomaPolinomios */

int main(int argc, char *argv[])
{
  Polinomio *P[3];
  int i;

  if (argc != 4) {
    printf("%s <polinomio1.txt> <polinomio2.txt> <resultado.txt>\n",argv[0]);
    exit(-1);
  }

  P[0] = LePolinomio(argv[1]);
  ImprimePolinomio(P[0]);
  P[1] = LePolinomio(argv[2]);
  ImprimePolinomio(P[1]);
  P[2] = SomaPolinomios(P[0],P[1]);
  ImprimePolinomio(P[2]);
  GravaPolinomio(P[2],argv[3]);

  for (i=0; i < 3; i++)
    DestroiPolinomio(&P[i]);

  return(0);
}

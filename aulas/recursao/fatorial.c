#include<stdio.h>
#include"cadeias.h"

/* Assumindo que n >= 0 */

long double fatorial_direta_fraca(unsigned long n){
  long double res; /* variável local */
  if (n <= 1) { /* condição de parada */
    res = 1.0; /* comando inicial */
    return(res);
  } else { /* n > 1 */
    /* sem comandos iniciais */
    res = fatorial_direta_fraca(n-1); /* chamada recursiva */
    res = res * n; /* comando final */ 
    return(res);
  }
}

/* Assumindo que x1 <= xn */

long double produto_direta_forte(unsigned long x1, \
				 unsigned long xn)
{
  unsigned long xm; /* variáveis locais */
  long double res1, res2;

  if (x1 == xn){ /* condição de parada */
    return(xn);
  } else { /* x1 < x n */
    xm   = (x1+xn)/2; /* comando inicial */
    res1 = produto_direta_forte(x1,xm);   /* chamada 1 */
    res2 = produto_direta_forte(xm+1,xn); /* chamada 2 */
    res2 = res2 * res1; /* comando final */
    return(res2);
  }
}

/* Assumindo que n >= 0 */

long double fatorial(unsigned long n)
{
  if (n <= 1) { /* caso trivial */
    return(1.0);
  } else { /* n > 1 */
    return(produto_direta_forte(1,n));
  }
}

int main(int argc, char **argv)
{
  unsigned long n;
  
  if (argc != 2){
    Erro("%s <número natural>","main",argv[0]); 
  }
  CadeiaParaNumero(argv[1],"unsigned long",&n);
  printf("Fatorial(%lu) = %LE\n", n, fatorial_direta_fraca(n));
  printf("Fatorial(%lu) = %LE\n", n, fatorial(n));

  return(0);
}

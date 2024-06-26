#include<stdio.h>
#include"cadeias.h"

bool Par(int n);
bool Impar(int n);


/* gcc recursao_indireta.c cadeias.c -o recursao_indireta */

/* Este exemplo verifica se um número natural é par por contagem
   regressiva até 0 */

bool Par(int n)
{
  if (n == 0)
    return(true);
  else
    return(Impar(n-1));
}

bool Impar(int n)
{
  if (n == 0)
    return(false);
  else
    return(Par(n-1));
}

int main(int argc, char **argv)
{
  int n;
  
  if (argc != 2){
    Erro("%s <número natural>","main",argv[0]); 
  }
  CadeiaParaNumero(argv[1],"int",&n);
  if (Par(n))
    printf("O número %d é par\n", n);
  else
    printf("O número %d é ímpar\n", n);

  if (Impar(n))
    printf("O número %d é ímpar\n", n);
  else
    printf("O número %d é par\n", n);

  return(0);
}

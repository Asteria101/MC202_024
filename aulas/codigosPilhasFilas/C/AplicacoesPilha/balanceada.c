#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PilhaDinamica.h"

/* Entre com uma expressão matemática do tipo: 

   ((a+b^c)*d-e) 

   O programa deverá verificar se os parênteses estão balanceados. 

   Para compilar: gcc balanceada.c PilhaDinamica.c -o balanceada
   Para executar: balanceada "((a+b^c)*d-e)"

*/


bool Balanceada(char *expressao)
{
  Pilha *pilha = CriaPilha();
  int    n     = strlen(expressao);

  for (int i=0; i < n; i++) {
    switch(expressao[i]){
    case '(':
      EmpilhaCaracter(&pilha,expressao[i]);
      break;
    case ')':
      if (PilhaVazia(pilha))
	return(false);     
      DesempilhaCaracter(&pilha);
      break;
    }
  }

  if (PilhaVazia(pilha))
    return(true);

  DestroiPilha(&pilha); /* empilhei mais '(' do que desempilhei */
  return(false);
}

int main(int argc, char **argv)
{

  if (argc != 2) {
    printf("%s <expressão matemática com parênteses>\n",argv[0]);
    exit(1);
  }

  
  if (Balanceada(argv[1]))
    printf("Expressão balanceada\n");
  else
    printf("Expressão desbalanceada\n");

  return(0);
}

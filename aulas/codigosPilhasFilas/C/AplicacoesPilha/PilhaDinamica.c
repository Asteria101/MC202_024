#include "PilhaDinamica.h"

Pilha *CriaPilha()
{
  return(NULL);
}
   
void   DestroiPilha(Pilha **pilha)
{
  while(!PilhaVazia(*pilha))
    DesempilhaValor(pilha);
}

bool   PilhaVazia(Pilha *pilha)
{
  if (pilha == NULL)
    return(true);

  return(false);
}

void   EmpilhaCaracter(Pilha **pilha, char caracter)
{
  Pilha *no = (Pilha *)calloc(1,sizeof(Pilha));

  no->caracter = caracter;
  no->prox     = *pilha;
  *pilha       = no;
}

char   DesempilhaCaracter(Pilha **pilha)
{
  if (!PilhaVazia(*pilha)){
    Pilha *no       = *pilha;
    char caracter   = no->caracter;
    *pilha          = no->prox;
    free(no);
    return(caracter);
  }
  
  printf("Aviso: Pilha vazia\n");
  return(' ');
}

void   EmpilhaValor(Pilha **pilha, float valor)
{
  Pilha *no = (Pilha *)calloc(1,sizeof(Pilha));

  no->valor    = valor;
  no->prox     = *pilha;
  *pilha       = no;
}

float  DesempilhaValor(Pilha **pilha)
{
  if (!PilhaVazia(*pilha)){
    Pilha *no       = *pilha;
    float valor     = no->valor;
    *pilha          = no->prox;
    free(no);
    return(valor);
  }
  
  printf("Aviso: Pilha vazia\n");
  return(0);
}


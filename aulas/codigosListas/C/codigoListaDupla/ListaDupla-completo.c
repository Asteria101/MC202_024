#include "ListaDupla.h"

ListaDupla *CriaListaDuplaVazia() /* Cria no-cabeca ficticio */
{
  ListaDupla *inicio = CriaNoDupla(0);

  return(inicio);
}
  
  
NoListaDupla *CriaNoDupla(int elem)
{
  NoListaDupla *p = (NoListaDupla *)calloc(1,sizeof(NoListaDupla));
  p->elem = elem;
  p->prox = p->ant = p; /* circularidade */

  return(p);
}
 
bool ListaDuplaVazia(ListaDupla *inicio)
{
  if (inicio == NULL) /* lista nunca foi criada */
    return(true);

  if (inicio->prox == inicio) /* apenas no-cabeca ficticio */
    return(true);
  
  return(false);
}

void ImprimeListaDupla(ListaDupla *inicio)
{
  NoListaDupla *p = inicio->prox;

  while (p != inicio) {

    if (p->ant == inicio) /* primeiro elemento */
      printf("(");
    printf("%d",p->elem);	
    if (p->prox == inicio) /* ultimo elemento */
      printf(")");
    else
      printf(", ");
    p = p->prox;
  }
  printf("\n");
}

bool BuscaElementoListaDupla(ListaDupla *inicio, int elem, NoListaDupla **pos)
{
  inicio->elem = elem;
  (*pos) = inicio->prox;
  
  while ((*pos)->elem != elem){ /* busca o elemento */
    (*pos) = (*pos)->prox;
  }
  if ((*pos) != inicio){ /* achou */
    return(true);
  } 

  return(false);
}

void InsereInicioListaDupla(ListaDupla *inicio, int elem)
{
  NoListaDupla *p = CriaNoDupla(elem);
  //*q = inicio->prox

  p->prox = inicio->prox;
  p->ant = inicio;
  inicio->prox->ant = p; //aponta o ultimo para o primeiro
  inicio->prox = p;   
}

void InsereFimListaDupla(ListaDupla *inicio, int elem)
{
  NoListaDupla *p = CriaNoDupla(elem), *q = inicio->ant;

  p->prox      = inicio;
  p->ant       = q;
  q->prox      = p;
  inicio->ant  = p;
}

bool InsereElementoAntesDaChaveListaDupla(ListaDupla *inicio, int elem, int chave)
{
  NoListaDupla *pos;

  if(BuscaElementoListaDupla(inicio, chave, &pos)){
    InsereInicioListaDupla(pos->ant, elem);
    return(true);
  }
  
  return(false);
}

bool  RemoveInicioListaDupla(ListaDupla *inicio, int *elem)
{
  NoListaDupla *p = inicio->prox;
  *elem = p->elem;

  if (!ListaDuplaVazia(inicio)){
    inicio->prox = p->prox;
    p->prox->ant = p->ant;
    free(p);
    return(true);
  }
  return(false);
}

bool RemoveElementoListaDupla(ListaDupla *inicio, int elem)
{
  NoListaDupla *pos;

  if(BuscaElementoListaDupla(inicio, elem, &pos)){
    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;
    free(pos);
    return(true);
  }

  return(false);
}

bool RemoveFimListaDupla(ListaDupla *inicio, int *elem)
{
  NoListaDupla *p = inicio->ant;
  *elem = p->elem;

  if (!ListaDuplaVazia(inicio)){
    inicio->ant = p->ant;
    p->ant->prox = p->prox;
    free(p);
    return(true);
  }
  return(false);
}

void EsvaziaListaDupla(ListaDupla *inicio)
{
  int elem;

  while (!ListaDuplaVazia(inicio))
    RemoveInicioListaDupla(inicio,&elem);
  
}

void DestroiListaDupla(ListaDupla **inicio)
{
  int elem;

  if (*inicio != NULL){
    while (!ListaDuplaVazia(*inicio))
      RemoveInicioListaDupla(*inicio,&elem);
    free(*inicio);
    *inicio = NULL;
  }
}



int main() {

  NoListaDupla *lista = CriaNoDupla(10);
  ImprimeListaDupla(lista);

  InsereInicioListaDupla(lista, 15);
  InsereInicioListaDupla(lista, 10);

  return 0;
}
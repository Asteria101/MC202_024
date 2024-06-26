#include "ListaDupla.h"

NoListaDupla *CriaNoDupla(int elem)
{
  NoListaDupla *no = (NoListaDupla *)malloc(sizeof(NoListaDupla));

  no->ant  = no->prox = no;
  no->elem = elem;

  return(no);
}

ListaDupla *CriaListaDuplaVazia() /* Cria no-cabeca ficticio */
{
  ListaDupla *inicio = CriaNoDupla(0);
  
  return(inicio);
}
  
  
 
bool ListaDuplaVazia(ListaDupla *inicio)
{
  if (inicio->prox == inicio)
    return(true);

  return(false);
}

void ImprimeListaDupla(ListaDupla *inicio)
{
  NoListaDupla *p = inicio->prox;

  /* imprime no-cabeca ficticio */
  if (ListaDuplaVazia(inicio)) /* no-cabeca lista vazia */ 
    printf("<-- (%p) X (%p) -->",inicio->ant,inicio->prox);
  else /* no-cabeca lista nao vazia */
    printf("<-- (%p) X (%p) ",inicio->ant,inicio->prox);

  while (p != inicio) {

    if (p->ant == inicio) /* primeiro elemento */
      printf(" <--> ");
    printf(" (%p) %d (%p) ",p->ant,p->elem,p->prox);	
    if (p->prox == inicio) /* ultimo elemento */
      printf(" --> ");
    else
      printf(" <--> ");
    p = p->prox;
  }
  printf("\n");
}

bool BuscaElementoListaDupla(ListaDupla *inicio, int elem, NoListaDupla **pos)
{
  /* coloca elemento no no-cabeca */

  inicio->elem = elem;

  /* busca elemento na lista */
  
  (*pos) = inicio->prox;
  while((*pos)->elem != elem)
    (*pos) = (*pos)->prox;


  /* verifica se o elemento foi encontrado */

  if ((*pos)==inicio) /* elemento nao encontrado */
    return(false);

  return(true);
}

void InsereInicioListaDupla(ListaDupla *inicio, int elem)
{

  NoListaDupla *p = CriaNoDupla(elem);

  p->ant = inicio->ant;
  p->prox = inicio;
  inicio->ant = p;

  ImprimeListaDupla(inicio);
}

void InsereFimListaDupla(ListaDupla *inicio, int elem)
{

  /* preencher */


}

bool InsereElementoAntesDaChaveListaDupla(ListaDupla *inicio, int elem, int chave)
{

  /* preencher */

}

bool  RemoveInicioListaDupla(ListaDupla *inicio, int *elem)
{

  /* preencher */

}

bool RemoveElementoListaDupla(ListaDupla *inicio, int elem)
{

  /* preencher */

}

bool RemoveFimListaDupla(ListaDupla *inicio, int *elem)
{

  /* preencher */

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

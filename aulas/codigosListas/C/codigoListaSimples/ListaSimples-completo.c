#include "ListaSimples.h"
 
bool ListaSimplesVazia(ListaSimples *inicio)
{
  if (inicio == NULL) 
    return(true);
  else
    return(false);
}

void ImprimeListaSimples(ListaSimples *inicio)
{
  while (inicio != NULL) {
    printf("%d --> ",inicio->elem);	
    inicio = inicio->prox;
  }
  printf("\n");
}

bool BuscaElementoListaSimples(ListaSimples *inicio, int elem, NoListaSimples **pos, NoListaSimples **ant)
{
  *ant = NULL; *pos = inicio;
  while (!ListaSimplesVazia(*pos)){
    if ((*pos)->elem==elem){
      return(true);
    } 
    *ant   = (*pos);
    *pos   = (*pos)->prox;    
  }
  return(false);
}

bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant){
  *pos = inicio;
  *ant = NULL;

  if (ListaSimplesVazia(inicio))
    return(false);

  while (((*pos)->prox != NULL)){ /* busca o ultimo elemento */
    (*ant) = (*pos);
    (*pos) = (*pos)->prox;
  }

  return(true);
}

NoListaSimples *CriaNoSimples(int elem)
{
  NoListaSimples *p = (NoListaSimples *)calloc(1,sizeof(NoListaSimples));
  p->elem = elem;
  p->prox = NULL;
  return(p);
}

void InsereInicioListaSimples(ListaSimples **inicio, int elem)
{
  NoListaSimples *p = CriaNoSimples(elem);

  p->prox = *inicio;
  *inicio =  p;
 
}

void InsereFimListaSimples(ListaSimples **inicio, int elem)
{
  NoListaSimples *p = CriaNoSimples(elem);
  NoListaSimples *pos, *ant;

  if (BuscaUltimoElementoListaSimples(*inicio,&pos,&ant)){
    pos->prox = p;
  } else { /* lista vazia */
    *inicio = p;
  }
}

bool InsereElementoAntesDaChaveListaSimples(ListaSimples **inicio, int elem, int chave)
{
  NoListaSimples *pos, *ant;

  if(BuscaElementoListaSimples(*inicio, chave, &pos, &ant)){
    if (ant == NULL) { /* chave esta no inicio */
      InsereInicioListaSimples(inicio, elem);
    } else {
      InsereInicioListaSimples(&pos, elem);
      ant->prox = pos;
    }
    return(true);
  }
  
  return(false);
}

bool  RemoveInicioListaSimples(ListaSimples **inicio, int *elem)
{
  NoListaSimples *p = *inicio;

  if (!ListaSimplesVazia(*inicio)){
    (*elem)   = (*inicio)->elem;
    (*inicio) = (*inicio)->prox; 
    free(p);
    return(true);
  }
 
  return(false);
}

bool RemoveElementoListaSimples(ListaSimples **inicio, int elem)
{
  NoListaSimples *pos, *ant;

  if (BuscaElementoListaSimples(*inicio,elem,&pos,&ant)){ 
   RemoveInicioListaSimples(&pos,&elem);
    if (ant == NULL) 
      (*inicio) = pos;
    else
      ant->prox = pos;
    return(true);
  }
  
  return(false);
}

bool  RemoveFimListaSimples(ListaSimples **inicio, int *elem)
{
  NoListaSimples *pos, *ant;

  if (BuscaUltimoElementoListaSimples(*inicio,&pos,&ant)){
    *elem = pos->elem;
    if (ant == NULL)
      (*inicio) = NULL;
    else
      ant->prox = pos->prox;
    free(pos);
    return(true);
  }

  return(false);
}

void DestroiListaSimples(ListaSimples **inicio)
{
  int elem;

  while (!ListaSimplesVazia(*inicio))
    RemoveInicioListaSimples(inicio,&elem);
}


void inverte(NoListaSimples *head) {
	NoListaSimples *p2 = head->prox, *p1 = NULL;
	while (p2->prox != NULL) {
		p2 = p2->prox;
		head->prox->prox = p1;
		p1 = head->prox;
		head->prox = p2;
	}
	p2->prox = p1;
}

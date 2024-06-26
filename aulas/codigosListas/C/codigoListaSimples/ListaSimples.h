#ifndef LISTA_SIMPLES_H_
#define LISTA_SIMPLES_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

typedef struct no_lista_simples {
    int elem;
    struct no_lista_simples *prox;
} ListaSimples, NoListaSimples;

bool ListaSimplesVazia(ListaSimples *inicio);
NoListaSimples *CriaNoSimples(int elem);
void ImprimeListaSimples(ListaSimples *inicio);
bool BuscaElementoListaSimples(ListaSimples *inicio, int elem, NoListaSimples **pos, NoListaSimples **ant);
bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant);
void InsereInicioListaSimples(ListaSimples **inicio, int elem);
void InsereFimListaSimples(ListaSimples **inicio, int elem);
bool InsereElementoAntesDaChaveListaSimples(ListaSimples **inicio, int elem, int chave);
bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem);
bool RemoveElementoListaSimples(ListaSimples **inicio, int elem);
bool RemoveFimListaSimples(ListaSimples **inicio, int *elem);
void DestroiListaSimples(ListaSimples **inicio);

#endif

#ifndef LISTA_DUPLA_H_
#define LISTA_DUPLA_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

/* Lista dupla circular e com no cabeca ficticio */

typedef struct no_lista_dupla {
    struct no_lista_dupla *ant;
    int elem;
    struct no_lista_dupla *prox;
} ListaDupla, NoListaDupla;

ListaDupla *CriaListaDuplaVazia();
NoListaDupla *CriaNoDupla(int elem);
void ImprimeListaDupla(ListaDupla *inicio);
bool BuscaElementoListaDupla(ListaDupla *inicio, int elem, NoListaDupla **pos);
void InsereInicioListaDupla(ListaDupla *inicio, int elem);
void InsereFimListaDupla(ListaDupla *inicio, int elem);
bool InsereElementoAntesDaChaveListaDupla(ListaDupla *inicio, int elem, int chave);
bool RemoveInicioListaDupla(ListaDupla *inicio, int *elem);
bool RemoveElementoListaDupla(ListaDupla *inicio, int elem);
bool RemoveFimListaDupla(ListaDupla *inicio, int *elem);
void EsvaziaListaDupla(ListaDupla *inicio);
void DestroiListaDupla(ListaDupla **inicio);

#endif

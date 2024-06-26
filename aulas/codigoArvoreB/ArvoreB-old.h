#ifndef _ARV_B_LIBDADOS_H_
#define _ARV_B_LIBDADOS_H_
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include <string.h>
//#include "libdados.h"


#define TAMMAX 511 /*Este eh o tamanho maximo de filhos */

typedef struct arvb {  /* Registro que representa nó em árvore B */
  int ordem; /*tamanho maximo desta arvore, que pode ser variavel*/
  int elems; /*quantidade de elementos ocupados da arvore*/
  int info[TAMMAX+1]; /*Vetor contendo todas as informacoes do no*/
  struct arvb *filhos[TAMMAX+2]; /*Vetor contendo todos os filhos */
} ArvB;

ArvB *ArvBCria(int ordem);
/* Cria uma arvore B com a ordem passada pelo parametro. Devolve NULL
   Caso a ordem seja maior do que o tamanho maximo especificado, ou 
   se deu algum pau de memoria
*/

int ArvBDestroi(ArvB **arvore);
/* Destroi a Arvore B. O apontador arvore deve retornar Nulo.
   int retorna 1 se tudo deu certo, ou 0 se deu algum tipo de pau.
*/

int ArvBInsere(ArvB **arvore, int valor);
/* Insere o elemento "Valor" na arvore "arvore". Devolve 1 se 
   deu tudo certo, devolve 0 se deu pau em alguma coisa.
   (por exemplo, se a arvore nao existe, ou se esse valor ja 
   existe na arvore).
*/

int ArvBBusca(ArvB *arvore, int valor);
/* Busca o valor "Valor" na arvore "arvore". 
   A funcao deve retornar 0 se o valor nao existir na arvore ou se 
   ocorrer algum tipo de Pau. Caso o valor esteja na arvore, a funcao
   deve retornar o nivel no qual o valor se encontra (a raiz 
   possui nivel 1
*/

int ArvBRemove(ArvB **arvore, int valor);
/* Remove o valor "valor" da arvore "arvore".
   retorna 0 caso o valor nao exista, ou caso de algum pau
   (como passarem uma arvore nula).
   retorna 1 caso tenha tido sucesso.
*/

void ArvBImprimePreOrdem(ArvB *arv, int nivel);

void ArvBImprime(ArvB *ab, int nivel, int filho);

#endif






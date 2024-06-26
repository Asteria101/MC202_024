#ifndef _ARV_B_LIBDADOS_H_
#define _ARV_B_LIBDADOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

#define NMAXREGS 511 /* Este é o número maximo (máxima ordem possóvel)
			de registros de um nó. */

typedef struct arvb {  /* Registro que representa nó em árvore B. Sua
			  árvore deve ser um índice primário e,
			  portanto, não poderá ter chaves
			  repetidas. */
  int ordem;  /* número máximo de registros em um nó da arvore que
		 está sendo criada */
  int nregs;  /* número de registros no nó */
  int chave[NMAXREGS+1]; /* vetor contendo as chaves dos registros em
			    ordem crescente. Uma posição extra é
			    necessária para acomodar o overflow
			    (número de chaves maior do que o
			    possível). */
  struct arvb *filha[NMAXREGS+2]; /* Vetor contendo apontadores para
			          as árvores filhas do nó. Uma posição
			          extra é necessária para acomodar o
			          overflow (número de filhas maior do
			          que o possível). */
} ArvB, NoArvB;

NoArvB *CriaNoArvB(int ordem);
/* Cria um nó da arvore B com a ordem passada como parametro. Devolve
   NULL caso a ordem seja maior do que o tamanho maximo especificado,
   ou menor que 2.
*/

bool DestroiArvB(ArvB **arvore);
/* Destroi a Arvore B. O apontador da arvore deve retornar NULL.
   A função retorna true se tudo deu certo, ou false no caso contrário.
*/

bool BuscaChaveArvB(ArvB *arvore, int chave, NoArvB **no, int *pos);
/* Busca a chave de um registro na arvore B.  A função deve retornar
   false se o valor não existir na árvore e abortar se a árvore não
   existir. Caso a chave esteja na árvore, a função deverá retornar o
   apontador para o nó que contém a chave e a sua posição no vetor de
   chaves em "pos".
*/

bool InsereArvB(ArvB **arvore, int chave);
/* Insere a chave na árvore B. Retorna true se deu tudo certo, retorna
   false se não foi possível a inserção (e.g., se o valor já existe).
*/

bool RemoveArvB(ArvB **arvore, int chave);
/* Remove a chave da arvore B, retornando false se a chave não for
   encontrada para remoção, abortando caso a árvore não exista, e
   retornando true caso a remoção tenha sido bem sucedida. */

void ImprimeArvBPreOrdem(ArvB *arv, int nivel);
void ImprimeArvB(ArvB *ab, int nivel, int filha);

#endif






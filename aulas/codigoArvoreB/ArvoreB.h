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

#define NMAXREGS 511 /* Este � o n�mero maximo (m�xima ordem poss�vel)
			de registros de um n�. */

typedef struct arvb {  /* Registro que representa n� em �rvore B. Sua
			  �rvore deve ser um �ndice prim�rio e,
			  portanto, n�o poder� ter chaves
			  repetidas. */
  int ordem;  /* n�mero m�ximo de registros em um n� da arvore que
		 est� sendo criada */
  int nregs;  /* n�mero de registros no n� */
  int chave[NMAXREGS+1]; /* vetor contendo as chaves dos registros em
			    ordem crescente. Uma posi��o extra �
			    necess�ria para acomodar o overflow
			    (n�mero de chaves maior do que o
			    poss�vel). */
  struct arvb *filha[NMAXREGS+2]; /* Vetor contendo apontadores para
			          as �rvores filhas do n�. Uma posi��o
			          extra � necess�ria para acomodar o
			          overflow (n�mero de filhas maior do
			          que o poss�vel). */
} ArvB, NoArvB;

NoArvB *CriaNoArvB(int ordem);
/* Cria um n� da arvore B com a ordem passada como parametro. Devolve
   NULL caso a ordem seja maior do que o tamanho maximo especificado,
   ou menor que 2.
*/

bool DestroiArvB(ArvB **arvore);
/* Destroi a Arvore B. O apontador da arvore deve retornar NULL.
   A fun��o retorna true se tudo deu certo, ou false no caso contr�rio.
*/

bool BuscaChaveArvB(ArvB *arvore, int chave, NoArvB **no, int *pos);
/* Busca a chave de um registro na arvore B.  A fun��o deve retornar
   false se o valor n�o existir na �rvore e abortar se a �rvore n�o
   existir. Caso a chave esteja na �rvore, a fun��o dever� retornar o
   apontador para o n� que cont�m a chave e a sua posi��o no vetor de
   chaves em "pos".
*/

bool InsereArvB(ArvB **arvore, int chave);
/* Insere a chave na �rvore B. Retorna true se deu tudo certo, retorna
   false se n�o foi poss�vel a inser��o (e.g., se o valor j� existe).
*/

bool RemoveArvB(ArvB **arvore, int chave);
/* Remove a chave da arvore B, retornando false se a chave n�o for
   encontrada para remo��o, abortando caso a �rvore n�o exista, e
   retornando true caso a remo��o tenha sido bem sucedida. */

void ImprimeArvBPreOrdem(ArvB *arv, int nivel);
void ImprimeArvB(ArvB *ab, int nivel, int filha);

#endif






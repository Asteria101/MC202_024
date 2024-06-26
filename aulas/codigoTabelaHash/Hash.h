#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

/* Tabela Hash com reespalhamento duplo e chaves k > 0: h(k,j) = ( (k
% m) + (j-1) (1+(k%m')) ) % m onde m' = m - 2 */

typedef struct _hash { 
  int *valor; /* valor da chave */ 
  int  m;     /* tamanho da tabela */
} Hash;


/* Cria tabela hash para armazenar ate n chaves, com reespalhamento
   duplo. */

Hash *CriaTabelaHash(int n); /* (1) m >= n, (2) m eh primo e o mais
				distante de potencia de 2, (3) m e
				(1+(k%m')) nao podem ter MDC, e (4)
				(1+(k%m')) > m. Inicializa ela com
				zeros para indicar posicao
				disponivel. */


char InsereChave(Hash *hash, int chave); /* retorna 1 se chave foi
					    inserida com sucesso e 0
					    no caso contrario. Usa
					    posicoes disponiveis com
					    valor -1, de chaves
					    anteriormente
					    removidas.*/

char RemoveChave(Hash *hash, int chave); /* retorna 1 se chave foi
					    removida com sucesso,
					    colocando marca -1 nas
					    posicoes que agora estao
					    disponiveis para novas
					    chaves. Retorna 0 no caso
					    contrario. */

/* Destroi a tabela */

void DestroiTabelaHash(Hash **hash);

/* Imprime a tabela */

void ImprimeTabelaHash(Hash *hash);

 
#endif 

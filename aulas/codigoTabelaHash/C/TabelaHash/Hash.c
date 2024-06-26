#include "Hash.h"

char EhPrimo(int numero)
{
  int i, n = sqrt(numero);

  if (numero==2)
    return(1);

  if ((numero%2)==0)
    return(0);

  for (i=3; i <= n; i=i+2) 
    if ((numero%i)==0)
      return(0);

  return(1);
}

int AchePrimoDistantePotencias2(int primeira, int segunda)
{
  int media = (primeira+segunda)/2, candidato[2];
 
  candidato[0]=media-1;
  candidato[1]=media+1;

  while((candidato[0] > primeira)&&(candidato[1]<segunda)){
    if (EhPrimo(candidato[0]))
      return(candidato[0]);
    if (EhPrimo(candidato[1]))
      return(candidato[1]);
    candidato[0]--;
    candidato[1]++;
  }

  printf("Nao existe primo entre %d e %d\n",primeira,segunda);
  exit(-1);
}

int Potencia2MaiorQueN(int n, int *expo)
{
  int pot2=2; 
  
  (*expo)=0;
  while (pot2 < n){
    pot2=pot2<<1;
    (*expo)++;
  }

  return(pot2);
}

/* (1) m >= n, (2) m eh primo e o mais distante de potencia de 2, (3)
   m e (1+(k%m')) nao podem ter MDC, e (4) (1+(k%m')) > m. Inicializa
   ela com zeros para indicar posicao disponivel. */

Hash *CriaTabelaHash(int n)
{
  Hash *hash=(Hash *)calloc(1,sizeof(Hash));
  int primeira, segunda, expo;

  primeira = Potencia2MaiorQueN(n,&expo);
  segunda  = 2<<(expo+1); /* shift-left que desloca os bits para à esquerda expo+1 vezes */ 
  hash->m  = AchePrimoDistantePotencias2(primeira, segunda);
  printf("A primeira potência de 2 acima de n=%d é %d e a segunda é %d\n",n,primeira,segunda);
  printf("O valor de m=%d é um primo mais distante dessas pontências de 2 e m'=%d.\n",hash->m,hash->m-2);
  hash->valor = (int *)calloc(hash->m,sizeof(int));
  
  return(hash);
}

/* retorna 1 se chave foi inserida com sucesso e 0 no caso
   contrario. Usa posicoes disponiveis com valor -1, de chaves
   anteriormente removidas. 

   h(k,j) = ( (k % m) + (j-1) (1+(k%m')) ) % m onde m' = m - delta 
   j=1,2,...,m tentativas
*/

char InsereChave(Hash *hash, int chave)
{
  int pos0, pos, j=1; 

  pos0 = pos = (chave % hash->m); 
  while ((hash->valor[pos]!=0)&&(hash->valor[pos]!=-1)&&(j <= hash->m)){
    j++;
    pos = (pos0 + (j-1)*(1+(chave%(hash->m-2))))%hash->m; 
  }
 
  if (j > hash->m) 
    return(0);
  
  hash->valor[pos]=chave;
  
  return(1);
}

/* retorna 1 se chave foi removida com sucesso, colocando marca -1 nas
   posicoes que agora estao disponiveis para novas chaves. Retorna 0
   no caso contrario. 

   h(k,j) = ( (k % m) + (j-1) (1+(k%m')) ) % m onde m' = m - delta 
   j=1,2,...,m tentativas

*/

char RemoveChave(Hash *hash, int chave) 
{
  int pos0, pos, j=1; 

  pos0 = pos = (chave % hash->m); 
  while ((hash->valor[pos]!=0)&&(hash->valor[pos]!=chave)&&(j <= hash->m)){
    j++;
    pos = (pos0 + (j-1)*(1+(chave%(hash->m-2))))%hash->m; 
  }
 
  if (j > hash->m) 
    return(0);
  
  if (hash->valor[pos]==0)
    return(0);
  
  hash->valor[pos]=-1;

  return(1);
}

/* Destroi a tabela */

void DestroiTabelaHash(Hash **hash)
{
  Hash *aux = *hash;

  free(aux->valor);
  free(aux);
  *hash = NULL;
}

/* Imprime a tabela */

void ImprimeTabelaHash(Hash *hash)
{
  int i;

  printf("Hash com %d posicoes\n",hash->m);
  for (i=0; i < hash->m; i++) 
    if ((hash->valor[i]!=0) && (hash->valor[i]!=-1))
      printf("pos %d valor %d\n",i,hash->valor[i]);
}

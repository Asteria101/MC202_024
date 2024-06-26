#include<stdio.h>
#include"cadeias.h"

/* gcc ordenacao_buscabinaria.c cadeias.c -o ordenacao_buscabinaria */

void Troca(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
  /* *x = *x + *y; */
  /* *y = *x - *y; */
  /* *x = *x - *y; */
}

int Particao(int *A, int p, int q)
{
  int x = A[p], i = p, j = q;
  do {
    while(A[i] <= x) i++;
    while(A[j] > x) j--;
    if (i < j) {
      Troca(&A[i],&A[j]);
      i++; j--;
    }
  } while(i < j);
  Troca(&A[p],&A[j]);
  return(j);
}


void OrdenaPorParticao(int *A, int p, int q)
{
  int r;
  if (p < q) {
    r = Particao(A, p, q);
    OrdenaPorParticao(A, p, r - 1);
    OrdenaPorParticao(A, r + 1, q);
  }
}

int *LeNumeros(char *nomearq, int *n)
{
  FILE *fp = fopen(nomearq,"r");
  int   *A = NULL;

  fscanf(fp,"%d\n",n);
  A = (int *)calloc((*n),sizeof(int));
  for (int i=0; i < (*n); i++) 
    fscanf(fp,"%d\n",&A[i]);
  fclose(fp);
  return(A);
}

/* Busca a chave em ch e retorna sua posição em pos, caso seja
   encontrada. Retorna true/false se encontrou ou não a chave
   procurada. */ 

bool BuscaBinaria(int *A,int p,int q,int ch,int *pos)
{
  if (p <= q){
    int r = (p+q)/2;
    if (A[r]==ch){
      *pos = r;
      return(true);
    } else{
      if (A[r] < ch)
	return(BuscaBinaria(A,r+1,q,ch,pos));
      else
	return(BuscaBinaria(A,p,r-1,ch,pos));
    }
  }

  return(false);
}

int main(int argc, char **argv)
{
  int n, *A, ch, pos;
  
  if (argc != 2){
    Erro("%s <arquivo texto com números inteiros>","main",argv[0]); 
  }

  A = LeNumeros(argv[1],&n);
  OrdenaPorParticao(A,0,n-1);
  for (int i=0; i < n; i++)
    printf("%d ",A[i]);
  printf("\n");

  printf("Entre com o valor que procura: ");
  scanf("%d",&ch);
  setbuf(stdin,NULL);

  if (BuscaBinaria(A,0,n-1,ch,&pos))
    printf("Elemento encontrado na posição %d\n",pos);
  else
    printf("Elemento não encontrado\n");
  
  return(0);
}

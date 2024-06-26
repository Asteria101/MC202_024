#include "ArvoreBinaria.h"
#include "ArvoreBinaria.c"

/* Constrói uma árvore binária a partir de dois percursos dados. 

   gcc ConstroiArvoreBinaria.c -o ConstroiArvoreBinaria

*/


int main(int argc, char **argv)
{
  ArvoreBinaria *T=NULL;
  char *s=NULL, *percurso;
  int   n;

  if (argc != 3) {
    printf("ConstroiArvoreBinaria <ordem-simetrica> <pos-ordem>\n");
    printf("cadeia com nós em ordem-simetrica (e.g., ''DBGEAFHC'')\n");
    printf("cadeia com nós em pós-ordem (e.g., ''DGEBHFCA'' \n");
    exit(1);
  }

  if (strlen(argv[1])!=strlen(argv[2])){
    printf("Percursos dados nao tem o mesmo tamanho\n");
    exit(1);
  }

  n = strlen(argv[1]);
  T = ConstroiArvoreBinariaSimPos(argv[1], argv[2], n); 

  ImprimeArvoreBinaria(T,0,Altura(T));
    
  s = (char *)calloc(n,sizeof(char));
  percurso = s;
  printf("Percurso em Pre-Ordem\n");
  VisitaPreOrdem(T,&s); /* s retorna apontando para o final da string */  
  printf("%s\n",percurso);

  s= percurso;
  printf("Percurso em Ordem Simetrica\n");
  VisitaOrdemSimetrica(T,&s); /* s retorna apontando para o final da string */  
  printf("%s\n",percurso);

  s= percurso;
  printf("Percurso em Pos-Ordem\n");
  VisitaPosOrdem(T,&s); /* s retorna apontando para o final da string */  
  printf("%s\n",percurso);

  
  char info = 'A', achou = 0;
  NoArvoreBinaria *no_ant = NULL;
  BuscaAnteriorSimetrica(T,&no_ant,info,&achou);
  if (achou)
    printf("Achou o no %c \n",no_ant->info);
    
  free(percurso);
  DestroiArvoreBinaria(&T);
 
  return(0);
}

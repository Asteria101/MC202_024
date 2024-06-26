#include "Hash.h"
#include "Hash.c"


/* gcc TestaHash.c -o TestaHash -lm */

int main()
{
  int chave, i, n, continua=1;
  Hash *hash;
  char opcao[10];

  printf("Entre com o numero de chaves\n");
  scanf("%d",&n);

  hash = CriaTabelaHash(n);


  printf("Entre com as %d chaves\n",n);
  for (i=0; i < n; i++) {
    scanf("%d",&chave);
    if (InsereChave(hash,chave)==0)
      printf("Chave %d nao pode ser inserida\n",chave);
  }
  
  ImprimeTabelaHash(hash);

  printf("Digite 0 para sair do programa\n");
  printf("Digite 1 para inserir nova chave\n");
  printf("Digite 2 para remover chave\n");

  scanf("%s",opcao);
  continua = atoi(opcao);

  while(continua) {

    switch(continua) {

    case 1:
      printf("Entre com uma chave para insercao\n");
      scanf("%d",&chave);

      if (InsereChave(hash,chave)==0) 
	printf("Chave %d nao pode ser inserida\n",chave);
      else
	ImprimeTabelaHash(hash);

      break;

    case 2:
      printf("Entre com uma chave para remocao\n");
      scanf("%d",&chave);
      
      if (RemoveChave(hash,chave)==0) 
	printf("Chave %d nao pode ser removida\n",chave);
      else
	ImprimeTabelaHash(hash);

      break;

    default:
      printf("Opcao invalida\n");
      continua=0;
    }

    printf("Digite 0 para sair do programa\n");
    printf("Digite 1 para inserir nova chave\n");
    printf("Digite 2 para remover chave\n");
    scanf("%s",opcao);
    continua = atoi(opcao);

  }

  return(0);
}

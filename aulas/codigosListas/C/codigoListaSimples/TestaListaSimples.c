#include "ListaSimples.h"

/* gcc TestaListaSimples.c ListaSimples.c -o TestaListaSimples */


int main()
{
  ListaSimples *inicio=NULL, *pos, *ant;
  int elem, continua=1, opcao, chave;

  while (continua) { 

    printf("Entre com uma das opcoes abaixo.\n");
    printf("0  - Inserir elemento no inicio da lista\n");
    printf("1  - Inserir elemento no final da lista\n");
    printf("2  - Inserir elemento antes de uma chave\n");
    printf("3  - Imprimir a lista \n");
    printf("4  - Buscar um elemento na lista \n");
    printf("5  - Buscar o ultimo elemento na lista \n");
    printf("6  - Remove elemento do inicio da lista\n");
    printf("7  - Remove elemento do final da lista\n");
    printf("8  - Remove um dado elemento da lista\n");
    printf("9  - Destroi a lista\n");
    printf("10 - Sai do programa\n\n");

    scanf("%d",&opcao);
    
    switch(opcao) { 

    case 0:
      printf("Entre com o elemento a ser inserido\n");
      scanf("%d",&elem);
      InsereInicioListaSimples(&inicio, elem);
      break;
    case 1:
      printf("Entre com o elemento a ser inserido\n");
      scanf("%d",&elem);
      InsereFimListaSimples(&inicio, elem);
      break;
    case 2:
      printf("Entre com o elemento a ser inserido e a chave \n");
      scanf("%d %d",&elem,&chave);
      InsereElementoAntesDaChaveListaSimples(&inicio, elem, chave);
      break;
    case 3:
      ImprimeListaSimples(inicio);
      printf("\n");
      break;
    case 4:
      printf("Entre com o elemento desejado \n");
      scanf("%d",&elem);
      if (BuscaElementoListaSimples(inicio,elem,&pos,&ant))      
	      printf("Elemento %d esta na posicao %p\n",pos->elem,pos);
      break;
    case 5:
      if (BuscaUltimoElementoListaSimples(inicio,&pos,&ant))
	      printf("Elemento %d esta na posicao %p\n",pos->elem,pos);
      break;
    case 6:
      if (RemoveInicioListaSimples(&inicio,&elem)){
	printf("%d foi removido\n",elem);
      }
      break;
    case 7:
      if (RemoveFimListaSimples(&inicio,&elem)){
	printf("%d foi removido\n",elem);
      }
      
      break;
    case 8:
      printf("Entre com o elemento a ser removido \n");
      scanf("%d",&elem);
      if (RemoveElementoListaSimples(&inicio,elem)){
	printf("%d foi removido\n",elem);
      }
      break;
    case 9:
      DestroiListaSimples(&inicio);
      break;
    case 10:
      DestroiListaSimples(&inicio);
      continua=0;
      break;
    default:
      printf("Opcao invalida\n");
    }

  }

return 0;
}

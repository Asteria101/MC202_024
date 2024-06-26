#include "ArvoreB.h"

/* gcc TestaArvoreB.c ArvoreB.c -o TestaArvoreB */


void ImprimeMenu()
{

  printf("Digite:\n");
  printf("i <valor> para inserir valor\n");
  printf("d <valor> para deletar valor\n");
  printf("p         para imprimir a arvore em pre-ordem\n");
  printf("I         para imprimir a figura da arvore \n");
  printf("s         para sair do programa\n");

}

int main()
{
  ArvB   *ab=CriaNoArvB(3);
  char   c;
  int    valor;


  ImprimeMenu();
  c = (char) fgetc(stdin);

  while (c != 's') {

    switch(c) {

    case 'i': 
      scanf("%d",&valor);
      InsereArvB(&ab,valor);
      break;
      
    case 'd':
      scanf("%d",&valor);
      RemoveArvB(&ab,valor);
      break;

    case 'p':
      ImprimeArvBPreOrdem(ab,1);
      break;

    case 'I':
      ImprimeArvB(ab,1,0);
      break;

    default:
      ImprimeMenu();
    }

    while ((c=(char)fgetc(stdin))=='\n');
  }

  DestroiArvB(&ab);

  return(0);
}

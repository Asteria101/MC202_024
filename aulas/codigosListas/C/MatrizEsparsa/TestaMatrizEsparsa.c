#include "MatrizEsparsa.h"

/* gcc TestaMatrizEsparsa.c MatrizEsparsa.c -o TestaMatrizEsparsa */

int main(int argc, char *argv[])
{
  MatrizEsparsa *M;


  /*----------------------------------------------------------------------*/

  void *trash = malloc(1);                 
  struct mallinfo info;   
  int MemDinInicial, MemDinFinal;
  free(trash); 
  info = mallinfo();
  MemDinInicial = info.uordblks;

  /*----------------------------------------------------------------------*/

  if (argc != 2) {
    printf("TestMatrizEsparsa <MatrizEsparsa.txt>\n");
    exit(-1);
  }

  M = LeMatrizEsparsa(argv[1]);
  ImprimeMatrizEsparsa(M);
  DestroiMatrizEsparsa(&M);



  /* -------------------------------------------------------------------- */

  info = mallinfo();
  MemDinFinal = info.uordblks;
  if (MemDinInicial!=MemDinFinal)
    printf("\n\nDinamic memory was not completely deallocated (%d, %d)\n",
	   MemDinInicial,MemDinFinal);   

  /* -------------------------------------------------------------------- */


  return(0);
}

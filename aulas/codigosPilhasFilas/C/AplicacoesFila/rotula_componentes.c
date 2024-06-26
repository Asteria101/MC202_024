#include "imagem.h"

/* gcc rotula_componentes.c imagem.c adjacencia.c Fila.c -o rotula_componentes */

int main(int argc, char **argv)
{
  if (argc != 5) {
    printf("%s <comp_binarios.pgm> <largura da adjacência> <altura da adjacência> <comp_coloridos.ppm>\n",argv[0]);
    exit(-1);
  }

  Imagem     *img = LeImagem(argv[1]);
  Adjacencia *adj = Retangular(atoi(argv[2]),atoi(argv[3]));
  Imagem     *rot = RotulaComponentes(img,adj);
  Imagem     *col = ColoreComponentes(rot);
  GravaImagem(col,argv[4]);
  
  DestroiImagem(&img);
  DestroiImagem(&rot);
  DestroiImagem(&col);
  DestroiAdjacencia(&adj);

  return(0);
}

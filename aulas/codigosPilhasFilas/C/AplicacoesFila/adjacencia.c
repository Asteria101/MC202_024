#include "adjacencia.h"

Adjacencia *CriaAdjacencia(int nadj)
{
  Adjacencia *adj = (Adjacencia *)calloc(1,sizeof(Adjacencia));

  adj->nadj = nadj;
  adj->dx   = (int *)calloc(nadj,sizeof(int));
  adj->dy   = (int *)calloc(nadj,sizeof(int));

  return(adj);
}

void DestroiAdjacencia(Adjacencia **adj)
{
  if ((*adj) != NULL){
    free((*adj)->dx);
    free((*adj)->dy);
    free(*adj);
    (*adj) = NULL;
  }
}

Adjacencia *Retangular(int w, int h)
{
  Adjacencia *adj = NULL;

  if (w % 2 == 0) w += 1;
  if (h % 2 == 0) h += 1;
  
  adj = CriaAdjacencia(w*h);

  int i = 0;
  for (int dy=-h/2; dy <= h/2; dy++){
    for (int dx=-w/2; dx <= w/2; dx++){
      adj->dx[i] = dx;
      adj->dy[i] = dy;
      i++;
    }
  }
  
  return(adj);
}

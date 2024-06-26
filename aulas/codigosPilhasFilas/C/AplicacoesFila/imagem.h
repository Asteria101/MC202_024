#ifndef _IMAGEM_H_
#define _IMAGEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "Fila.h"
#include "adjacencia.h"

typedef struct _imagem {
  int ***banda; /* armazena o valor do pixel em cada banda da imagem */
  int nx, ny;   /* números de pixels nos eixos x (horizontal, colunas da
		   matriz) e y (vertical, linhas da matriz) */
  int nbandas;  /* número de bandas */
} Imagem;

Imagem *CriaImagem(int nx, int ny, int nbandas);
void   *DestroiImagem(Imagem **img);
Imagem *LeImagem(char *nome_img);
void    GravaImagem(Imagem *img, char *nome_img);
Imagem *RotulaComponentes(Imagem *img, Adjacencia *adj);
Imagem *ColoreComponentes(Imagem *img);


#endif

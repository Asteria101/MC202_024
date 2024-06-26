#include<stdio.h>
#include"cadeias.h"

/* gcc backtrack.c cadeias.c -o backtrack */

/* Busca a saída de um labirinto a partir de uma posição inicial,
   andando com vizinhança-4. As posições são de três tipos: ' ' -
   válida, 'X' - inválida, e 'S' - saída. */

typedef struct _ponto {
  int x, y;
} Ponto;

typedef struct _labirinto {
  char **Posicao;
  int nx, ny;
  Ponto entrada, saida;
} Labirinto;

Labirinto *LeLabirinto(char *nomearq)
{
  FILE *fp = fopen(nomearq,"r");
  Labirinto *L = (Labirinto *)calloc(1,sizeof(Labirinto));
  
  fscanf(fp,"%d %d\n",&L->nx,&L->ny);
  L->Posicao = (char **)calloc(L->ny,sizeof(char *));
  for (int y=0; y < L->ny; y++) 
    L->Posicao[y] = (char *)calloc(L->nx,sizeof(char ));

  for (int y=0; y < L->ny; y++){ 
    for (int x=0; x < L->nx; x++) {
      fscanf(fp,"%c",&L->Posicao[y][x]);
      if (L->Posicao[y][x]=='E'){
	L->entrada.x= x; L->entrada.y= y;
	L->Posicao[y][x]='P';
      } else {
	if (L->Posicao[y][x]=='S'){
	  L->saida.x= x; L->saida.y= y;
	  L->Posicao[y][x]='P';
	}
      }
    }
    fscanf(fp,"\n");
  }

  fclose(fp);
  return(L);
}

void DestroiLabirinto(Labirinto **L)
{
  if ((*L)!=NULL){
    for (int y=0; y < (*L)->ny; y++)
      free((*L)->Posicao[y]);
    free((*L)->Posicao);
    free((*L));
    (*L) = NULL;
  }
}

bool Backtrack(Labirinto *L, Ponto P)
{
  bool res = false;




  return(res);
}

int main(int argc, char **argv)
{
  Labirinto *L = NULL;
  
  if (argc != 2){
    Erro("%s <arquivo texto do labirinto>","main",argv[0]); 
  }
  
  L = LeLabirinto(argv[1]);

  /* for (int y=0; y < L->ny; y++){  */
  /*   for (int x=0; x < L->nx; x++) { */
  /*     printf("%c",L->Posicao[y][x]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  if (Backtrack(L,L->entrada))
    printf("Encontrou a saída em (%d,%d)\n",L->saida.x,L->saida.y);
  else
    printf("Labirinto sem saída\n");
	   
  return(0);
}

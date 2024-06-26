#include "ArvoreBinaria.h"

/* --------------------------  Privadas -------------------------------------  */

void NumeroNosEsquerdaDireita(char *sim, char raiz, int *ne, int *nd); 
void NosEsquerdaDireitaSim(char *sim, int ne, int nd, char **esq_sim, char **dir_sim);
void NosEsquerdaDireitaPos(char *pos, int ne, int nd, char **esq_pos, char **dir_pos);

/* Encontra numeros de nos ne e nd das subarvores esquerda e direita */

void NumeroNosEsquerdaDireita(char *sim, char raiz, int *ne, int *nd)
{
  int i, n = strlen(sim);
  
  *ne = *nd = i = 0; 
  while (sim[i]!=raiz){
    i++;
  }
  (*ne) = i; 
  (*nd) = n - (*ne) - 1;
}

void NosEsquerdaDireitaSim(char *sim, int ne, int nd, char **esq_sim, char **dir_sim)
{
  int i, j;

  /* Copia nos da subarvore esquerda */

  if (ne > 0){
    *esq_sim = (char *)calloc(ne,sizeof(char));
    for (i=0; i < ne; i++) 
      (*esq_sim)[i] = sim[i];
  }else{
    *esq_sim = NULL;
  }

  /* Copia nos da subarvore direita */

  if (nd > 0) {
    *dir_sim = (char *)calloc(nd,sizeof(char));
    for (i=0, j=ne+1; i < nd; i++,j++) 
      (*dir_sim)[i] = sim[j];
  } else {
    *dir_sim = NULL;
  }
}

void NosEsquerdaDireitaPos(char *pos, int ne, int nd, char **esq_pos, char **dir_pos)
{
  int i, j;

  /* Copia nos da subarvore esquerda */

  if (ne > 0){
    *esq_pos = (char *)calloc(ne,sizeof(char));
    for (i=0; i < ne; i++) 
      (*esq_pos)[i] = pos[i];
  }else{
    *esq_pos = NULL;
  }

  /* Copia nos da subarvore direita */

  if (nd > 0) {
    *dir_pos = (char *)calloc(nd,sizeof(char));
    for (i=0, j=ne; i < nd; i++,j++) 
      (*dir_pos)[i] = pos[j];
  } else {
    *dir_pos = NULL;
  }
}

/* --------------------------- Publicas -------------------------------------- */

/* Cria no de arvore binaria com subarvores esquerda e direita */

NoArvoreBinaria *CriaNoArvoreBinaria(ArvoreBinaria *esq, ArvoreBinaria *dir, char info)
{
  NoArvoreBinaria *p = (NoArvoreBinaria *)calloc(1,sizeof(NoArvoreBinaria));
  p->esq   = esq;
  p->dir   = dir;
  p->info  = info;
  return p;
}

/* Constroi arvore binaria a partir de strings de tamanho n com os
   percursos em ordem simetria e pos-ordem */

ArvoreBinaria *ConstroiArvoreBinariaSimPos(char *sim, char *pos, int n)
{
  char *esq_sim=NULL,*dir_sim=NULL,*esq_pos=NULL,*dir_pos=NULL; 
  int   ne, nd; 
  NoArvoreBinaria *p=NULL, *esq=NULL, *dir=NULL; 


  if (n == 1) { 
    p = CriaNoArvoreBinaria(NULL,NULL,sim[0]);
    
  } else { /* n > 1 */ 
    NumeroNosEsquerdaDireita(sim,pos[n-1],&ne,&nd);

    NosEsquerdaDireitaSim(sim,ne,nd,&esq_sim,&dir_sim);

    NosEsquerdaDireitaPos(pos,ne,nd,&esq_pos,&dir_pos);

    if (esq_sim != NULL)
      esq = ConstroiArvoreBinariaSimPos(esq_sim, esq_pos, strlen(esq_sim));
    if (dir_sim != NULL)
      dir = ConstroiArvoreBinariaSimPos(dir_sim, dir_pos, strlen(dir_sim));
    p = CriaNoArvoreBinaria(esq,dir,pos[n-1]);
  }

  return(p);
}

int Altura(ArvoreBinaria *T)
{
  if (T != NULL) 
    return(1 + MAX(Altura(T->esq),Altura(T->dir)));
  else
    return(0);
}

void ImprimeArvoreBinaria(ArvoreBinaria *T, int h, int altura)
{
  int i;

  if (T != NULL) {
    ImprimeArvoreBinaria(T->dir, h+1, altura);
    for (i=0; i < h; i++) 
      printf("   ");
    printf("%c",T->info);
    for (i=0; i < altura-h; i++) 
      printf("---");
    printf("\n");
    ImprimeArvoreBinaria(T->esq, h+1,altura);    
  }
}

void VisitaPreOrdem(ArvoreBinaria *T, char **s)
{
  if (T != NULL) {
    sprintf(*s,"%c ",T->info);
    (*s) = (*s) + strlen(*s);
    VisitaPreOrdem(T->esq, s);
    VisitaPreOrdem(T->dir, s);
  }
}

void VisitaOrdemSimetrica(ArvoreBinaria *T, char **s)
{
  if (T != NULL) {
    VisitaOrdemSimetrica(T->esq, s);
    sprintf(*s,"%c ",T->info);
    (*s) = (*s) + strlen(*s);
    VisitaOrdemSimetrica(T->dir, s);
  }
}

void VisitaPosOrdem(ArvoreBinaria *T, char **s)
{
  if (T != NULL) {
    VisitaPosOrdem(T->esq, s);
    VisitaPosOrdem(T->dir, s);    
    sprintf(*s,"%c ",T->info);
    (*s) = (*s) + strlen(*s);
  }
}


void DestroiArvoreBinaria(ArvoreBinaria **T)
{
  NoArvoreBinaria *p=*T;

  if (p != NULL){
    DestroiArvoreBinaria(&(p->esq));
    DestroiArvoreBinaria(&(p->dir));
    free(p);
    *T = NULL;
  }
}

void BuscaAnteriorSimetrica(ArvoreBinaria *T, NoArvoreBinaria **no_ant, char info, char *achou)
{
  if ((T != NULL)&&(!(*achou))){
    BuscaAnteriorSimetrica(T->esq,no_ant,info,achou);
    if (!(*achou)){
      if (T->info != info){
	(*no_ant) = T;
	BuscaAnteriorSimetrica(T->dir,no_ant,info,achou);
      } else {
	if (*no_ant != NULL)
	  (*achou)=1;
      }
    }
  }
}

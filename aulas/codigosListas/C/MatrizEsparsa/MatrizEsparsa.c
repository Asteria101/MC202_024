#include "MatrizEsparsa.h"

/* --------------------- Privadas ---------------------------------*/

void VerificaSePrecisaDeMaisNosCabecasNasColunas(MatrizEsparsa *M, int col);
void VerificaSePrecisaDeMaisNosCabecasNasLinhas(MatrizEsparsa *M, int lin);
bool BuscaColuna(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int col);
bool BuscaLinha(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int lin);
NoMatrizEsparsa *PosicaoInsercaoNaColuna(MatrizEsparsa *M, int lin, int col);
NoMatrizEsparsa *PosicaoInsercaoNaLinha(MatrizEsparsa *M, int lin, int col);

/* Retorna em pos o ponteiro do elemento da coluna col, encontrado
   apartir de inicio. */

bool BuscaColuna(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int col)
{
  while (((*pos)->col < col)&&((*pos)->direita != inicio)){
    (*pos) = (*pos)->direita;
  }
  if ((*pos)->col == col) 
    return(true);
  else
    return(false);
}

/* Retorna em pos o ponteiro do elemento da linha lin, encontrado
   apartir de inicio. */

bool BuscaLinha(NoMatrizEsparsa *inicio, NoMatrizEsparsa **pos, int lin)
{
  while (((*pos)->lin < lin)&&((*pos)->abaixo != inicio)){
    (*pos) = (*pos)->abaixo;
  }
  if ((*pos)->lin == lin) 
    return(true);
  else
    return(false);
}

/* Retorna em pos o ponteiro do elemento encontrado na matriz */

bool BuscaElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, NoMatrizEsparsa **pos)
{
  NoMatrizEsparsa *inicio;

  *pos = M->direita;
  if (BuscaColuna(M,pos,col)){ 
    inicio = *pos;
    if (BuscaLinha(inicio,pos,lin)){
      return(true);
    }
  }

  return(false);
}

void VerificaSePrecisaDeMaisNosCabecasNasColunas(MatrizEsparsa *M, int col)
{
  int ncol = NumeroColunasMatrizEsparsa(M),c;
  NoMatrizEsparsa *p,*q; 

  if (ncol-1 < col) { /* necessita de mais nos cabecas nas colunas */
    p = M; 
    while(p->direita != M) /* vai para a ultima posicao da lista de nos
			  cabecas das colunas */
      p=p->direita;

      for (c=ncol; c <= col; c++) { /* aumenta a lista de nos cabecas
				       das colunas */
	q = CriaNoMatrizEsparsa(-1,c,0.0);
	p->direita = q;
	q->direita = M;
	p      = q;
      }
    }
}

void VerificaSePrecisaDeMaisNosCabecasNasLinhas(MatrizEsparsa *M, int lin)
{
  int nlin = NumeroLinhasMatrizEsparsa(M),l;
  NoMatrizEsparsa *p,*q; 

  if (nlin-1 < lin) { /* necessita de mais nos cabecas nas linhas */
    p = M; 
    while(p->abaixo != M) /* vai para a ultima posicao da lista de
			    nos cabecas das linhas */
      p=p->abaixo;

    for (l=nlin; l <= lin; l++) { /* aumenta a lista de nos cabecas
				     das linhas */
      q = CriaNoMatrizEsparsa(l,-1,0.0);
      p->abaixo = q;
      q->abaixo = M;
      p      = q;
    }
  }
}

NoMatrizEsparsa *PosicaoInsercaoNaColuna(MatrizEsparsa *M, int lin, int col)
{
  NoMatrizEsparsa *pos,*pos_ant,*inicio_col;

  /* identifica apontador de inicio da coluna para insercao */

  pos = M->direita; 
  while (pos->col != col)
    pos = pos->direita;
  
  inicio_col = pos;

  /* percorre os elementos da coluna para identificar o ponto de
     inserçao */
  
  pos_ant = pos; pos=pos->abaixo;    
  while ((pos->lin < lin)&&(pos!=inicio_col)){  
    pos_ant = pos;
    pos     = pos->abaixo;
  }

  return(pos_ant);
}

NoMatrizEsparsa *PosicaoInsercaoNaLinha(MatrizEsparsa *M, int lin, int col)
{
  NoMatrizEsparsa *pos,*pos_ant,*inicio_lin;

  /* identifica apontador de inicio da linha para insercao */

  pos = M->abaixo; 
  while (pos->lin != lin)
    pos = pos->abaixo;
    
  inicio_lin = pos; 

  /* percorre os elementos da linha para identificar o ponto de
     inserçao */

  pos_ant = pos; pos=pos->direita;  
  while ((pos->col < col)&&(pos != inicio_lin)){       
      pos_ant = pos; 
      pos     = pos->direita;
    }

  return(pos_ant);
}


/* --------------------- Publicas ---------------------------------*/

NoMatrizEsparsa *CriaNoMatrizEsparsa(int lin, int col, float valor)
{
  NoMatrizEsparsa *q = (NoMatrizEsparsa *)calloc(1,sizeof(NoMatrizEsparsa));
  q->lin    = lin; 
  q->col    = col; 
  q->valor  = valor; 
  q->direita    = q;
  q->abaixo = q;

  return(q);
}

MatrizEsparsa *CriaMatrizEsparsaVazia()
{
  NoMatrizEsparsa *M=CriaNoMatrizEsparsa(-1,-1,0.0); /* no cabeca */

  return(M);
}

int NumeroLinhasMatrizEsparsa(MatrizEsparsa *M)
{
  int nlin=0; 
  NoMatrizEsparsa *p=M;

  while (p->abaixo != M) {
    nlin++;
    p = p->abaixo;
  }

  return(nlin);
}

int NumeroColunasMatrizEsparsa(MatrizEsparsa *M)
{
  int ncol=0; 
  NoMatrizEsparsa *p=M;

  while (p->direita != M) {
    ncol++;
    p = p->direita;
  }

  return(ncol);
}

bool MatrizEsparsaVazia(MatrizEsparsa *M)
{
  if (M != NULL){
    if ((M->abaixo == M)&&(M->direita == M))
      return(true);
    else
      return(false);
  } else 
    return(false);
}

MatrizEsparsa *LeMatrizEsparsa(char *arq)
{
  FILE *fp=fopen(arq,"r");
  int i, nelems, lin, col;
  float valor;
  MatrizEsparsa *M=CriaMatrizEsparsaVazia();
  
  fscanf(fp,"%d\n",&nelems);
  for (i=0; i < nelems; i++) {
    fscanf(fp,"%d %d %f\n",&lin,&col,&valor);
    InsereElemMatrizEsparsa(M,lin,col,valor);    
  }
  fclose(fp);

  return(M);
}



void InsereElemMatrizEsparsa(MatrizEsparsa *M, int lin, int col, float valor)
{
  NoMatrizEsparsa *pos, *linha_pos_ant, *coluna_pos_ant;

  if (BuscaElemMatrizEsparsa(M,lin,col,&pos)){ /* atualiza valor, caso o
						  elemento ja esteja na
						  matriz */
    printf("Atualizando valor de %f para %f em (%d,%d)\n",pos->valor,valor,lin,col);
    pos->valor = valor;

  } else {
    VerificaSePrecisaDeMaisNosCabecasNasColunas(M,col);
    VerificaSePrecisaDeMaisNosCabecasNasLinhas(M,lin);
    coluna_pos_ant = PosicaoInsercaoNaColuna(M, lin, col);
    linha_pos_ant  = PosicaoInsercaoNaLinha(M, lin, col);

    /* Cria e insere novo no */

    pos = CriaNoMatrizEsparsa(lin,col,valor); /* cria o novo no */
    pos->abaixo            = coluna_pos_ant->abaixo;
    coluna_pos_ant->abaixo = pos;
    pos->direita               = linha_pos_ant->direita;
    linha_pos_ant->direita     = pos;

    //    ImprimeMatrizEsparsa(M);  
  }
}

void DestroiMatrizEsparsa(MatrizEsparsa **M)
{
  MatrizEsparsa   *aux=*M;
  NoMatrizEsparsa *p, *q, *inicio;

  /* libera memoria dos nos internos */

  inicio = aux->direita;
  while (inicio != aux) {
    p = inicio->abaixo;
    while (p != inicio) { /* enquanto a coluna nao estiver vazia */
      q = p->abaixo;
      free(p);
      p = q;
    }
    inicio = inicio->direita;
  }

  /* libera nos cabecas das colunas */

  inicio = aux->direita;
  while (inicio != aux){
    q = inicio->direita;
    free(inicio);
    inicio = q;
  }

  /* libera nos cabecas das linhas */

  inicio = aux->abaixo;
  while (inicio != aux){
    q = inicio->abaixo;
    free(inicio);
    inicio = q;
  }
  
  free(aux); /* libera no cabeca da matriz */
  *M = NULL; 
}

void ImprimeMatrizEsparsa(MatrizEsparsa *M)
{
  int c,l,ncol,nlin;
  NoMatrizEsparsa *p;

  ncol = NumeroColunasMatrizEsparsa(M);
  nlin = NumeroLinhasMatrizEsparsa(M);

  for (l=0; l < nlin; l++) {    
    for (c=0; c < ncol; c++) {
      if (BuscaElemMatrizEsparsa(M,l,c,&p))
	printf("%5.2f ",p->valor);
      else
	printf("%5.2f ",0.0);
    }
    printf("\n");
  }
  printf("\n");
}



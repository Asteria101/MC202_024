#include "ArvoreB.h"

/* -------------------- Funções Privadas -----------------------------------*/

bool ArvBVazia(ArvB *arvore);
/* ArvBVazia retorna true se a árvore estiver vazia (i.e., possui ao
   menos um nó raiz, mas sem chaves ainda). Retorna false no caso
   contrário, mas aborta o processo se não existir uma árvore. */

bool BuscaChaveNoArvB(NoArvB *no, int chave, int *pos);
/* BuscaChaveNo recebe um nó da arvore B e procura a chave neste nó.
   Assumindo que as chaves são mantidas em ordem crescente no nó, os
   seguintes eventos podem ocorrer: (1) A chave não está neste nó. A
   função deve retornar false e "pos" deve retornar com a posição da
   árvore filha na qual a chave poderá ser encontrada. (2) A chave
   está neste nó. A função deverá retornar true e a posição da chave
   em "pos". */

void InsereChaveEFilhaEmNo(ArvB *no, ArvB *filha_dir, int chave, int pos);
/* InsereChaveEFilhaEmNo: Coloca os novos membros (chave e
   filha da direita) nas posições corretas. */

bool NoComMaisChavesQuePossivel(NoArvB *no);
/* NoComMaisChavesQuePossivel retorna true se o nó estourou, e false
   caso contrário */

bool NoComMenosChavesQuePermitido(NoArvB *no);
/* NoComMenosChavesQuePermitido retorna true se o nó tem menos chaves
   do que permitido e false no caso contrário */

int TrataNoComMaisChavesQuePossivel(NoArvB **no, NoArvB **filha_dir);
/* TrataNoComMaisChavesQuePossivel divide o nó com overflow e retorna
   a chave mediana e sua filha à direita para inserção no nó pai. */

void TrataNoComMenosChavesQuePermitido(NoArvB **no, int posicao);
/* TrataNoComMenosChavesQuePermitido tenta pegar emprestada uma chave
   de uma das irmãs e se não for possível, une nós. */


bool InsereArvBRec(NoArvB **no, NoArvB **filha_dir, int *chave, bool *overflow);
/* InsereArvBRec busca recursivamente pelo nó folha para inserir nova
   chave, trata possível overflow após a recursão, e retorna
   true. Retorna false se a chave já existir na árvore B. */


void TrocaChaveComAntecessora(NoArvB *no, int pos);
/* TrocaChaveComAntecessora: busca a chave antecessora da chave que
   está na posição "pos" no nó em "no", e troca ela com a antecessora
   para fins de reduzir a remoção sempre a um nó folha.*/

void RemoveChaveEmNo(NoArvB *no, int pos);
/* RemoveChaveEmNo recebe um no da arvore B e uma posicao; remove a
   chave nesta posicao, transladando de uma posicao para trás as
   chaves e filhas posteriores. Diminui de 1 o número de chaves no
   nó. */

bool RemoveArvBRec(NoArvB **no, int chave, bool *underflow);
/* RemoveArvBRec busca recursivamente pela chave e se ela existir,
   remove-a, trata possível underflow após a recursão, e retorna
   true. Caso contrário, retorna false. */  

bool ArvBVazia(ArvB *arvore)
{
  if (arvore == NULL){
    printf("Erro em ArvBVazia: Árvore inexistente\n");
    exit(-1);
  }
  
  if (arvore->nregs==0)
    return(true);
  
  return(false);
}

bool BuscaChaveNoArvB(NoArvB *no, int chave, int *pos)
{
  for ((*pos)=0; (no->chave[*pos] < chave) && (*pos) < no->nregs; (*pos)++);

  /* "pos" contém a posição da chave no nó */
  if (((*pos) < no->nregs)&&(no->chave[*pos] == chave))
    return true;

  /* "pos" contém a posição da árvore filha na qual a chave poderá ser
     encontrada */
  return(false);
}

void InsereChaveEFilhaEmNo(ArvB *no, ArvB *filha_dir, int chave, int pos)
{
  /* Desloca as chaves para a direita para caber a chave nova */
  for (int i = no->nregs; i > pos; i--) {
    no->chave[i]   = no->chave[i-1];
    no->filha[i+1] = no->filha[i];
  }
  
  /* Insere a nova chave e sua filha à direita */
  no->chave[pos]   = chave;
  no->filha[pos+1] = filha_dir;
  no->nregs++;
}
 
bool NoComMaisChavesQuePossivel(NoArvB *no)
{
  return(no->nregs > no->ordem);
}

bool NoComMenosChavesQuePermitido(NoArvB *no)
{
  return(no->nregs < (no->ordem/2));
}

int TrataNoComMaisChavesQuePossivel(NoArvB **no, NoArvB **filha_dir)
{
  int chave, mediana;

  /* cria um novo nó que será a filha à direita da chave mediana no nó
     pai. */
  
  (*filha_dir) = CriaNoArvB((*no)->ordem);
  mediana      = (((*no)->ordem)+1)/2;
  chave        = (*no)->chave[mediana];
  (*no)->nregs = mediana;
  
  /* Copia as chaves e filhas para o novo nó (filha à direita da mediana no nó pai). */
  int pos;
  for (pos = mediana+1; pos <= (*no)->ordem; pos++) {
    (*filha_dir)->chave[pos-(mediana+1)] = (*no)->chave[pos];
    (*filha_dir)->filha[pos-(mediana+1)] = (*no)->filha[pos];
    (*no)->filha[pos] = NULL;
  }

  /* copia a filha à direita da última chave */
  (*filha_dir)->filha[pos-(mediana+1)] = (*no)->filha[pos];
  (*no)->filha[pos] = NULL;
  
  /* inicializa o número de registros do novo nó */
  (*filha_dir)->nregs = ((*no)->ordem)/2;

  return(chave);
}

bool InsereArvBRec(NoArvB **no, NoArvB **filha_dir, int *chave, bool *overflow)
{
  int pos=0, j=0;

  if (*no==NULL){ /* trata-se de uma filha de nó folha */
    *overflow = true;   /* para forçar a inserção no nó pai na volta
		           da recursão */
    *filha_dir = NULL; /* inicializa a árvore filha com NULL */ 
    return(true);
  }
  
  if(BuscaChaveNoArvB(*no, *chave, &pos)) {
      /* Chave encontrada na árvore, ignora a sua inserção. */
      (*overflow) = false;
      return(false);
  }
  
  if (InsereArvBRec(&((*no)->filha[pos]), filha_dir, chave, overflow)) {

	/* Insere recursivamente o elemento no nó apropriado. */
	if (*overflow) {
	  
	  /* Esta situação vai ocorrer em dois casos: (1) A chave é
	     nova e precisa ser inserida no nó ou (2) a chave é a
	     mediana do nó filho que quebrou por overflow e esta
	     mediana (retornada em "chave") precisa ser inserida neste
	     nó. A inserção se dará na posição "pos" e deve-se ainda
	     verificar se o nó será quebrado por excesso de chaves. */
	  
	  InsereChaveEFilhaEmNo(*no, *filha_dir, *chave, pos);
	  
	  if (NoComMaisChavesQuePossivel(*no)) { /* o nó está com mais chaves do que possível */	
	    (*chave)    = TrataNoComMaisChavesQuePossivel(no, filha_dir);	
	    (*overflow) = true;
	  } else { 
	    (*overflow) = false; /* foi possível acomodar a nova chave */
	  }
	}
	
	return true;
  }
  
  return false;      
}


void TrocaChaveComAntecessora(NoArvB *no, int pos)
{
  ArvB *no_aux;
  int   chave_aux;
  
  no_aux = no->filha[pos]; /* árvore filha à esquerda da chave na
			      posição "pos" */
  while(no_aux->filha[no_aux->nregs]!=NULL) /* busca a chave mais à
					       direira na àrvore
					       esquerda (i.e., a
					       antecessora da chave
					       que está em "no" na
					       posição "pos") */
    no_aux = no_aux->filha[no_aux->nregs];

  /* troca a chave por sua antecessora na árvore B */
  chave_aux      = no->chave[pos];
  no->chave[pos] = no_aux->chave[no_aux->nregs-1];
  no_aux->chave[no_aux->nregs-1] = chave_aux;
}

void RemoveChaveEmNo(NoArvB *no, int pos)
{
  int i;
  /* desloca as chaves e filhas para trás */
  for(i=pos; i < no->nregs; i++)
    {
      no->chave[i] = no->chave[i+1];
      no->filha[i] = no->filha[i+1];
    }
  /* completa o deslocamento para a filha à direita da última chave */ 
  no->filha[i]   = no->filha[i+1];
  no->filha[i+1] = NULL;
  /* ajusta o número de registros */
  no->nregs--;
}

void TrataNoComMenosChavesQuePermitido(NoArvB **no, int pos)
{
  int chave,i,j;
  NoArvB *irma_esq=NULL, *filha=NULL, *irma_dir=NULL;

  filha = (*no)->filha[pos];
  
  if (pos > 0) { /* existe irmã à esquerda da filha */ 
    irma_esq = (*no)->filha[pos-1];
    if(irma_esq->nregs > (((*no)->ordem)/2)) { /* A irmã à esquerda
						  tem chaves para
						  emprestar. A sua
						  última chave sobe
						  para o nó pai e a
						  chave do nó pai
						  desce para a filha
						  na posição mais à
						  esquerda. A filha à
						  direira da chave que
						  subiu passa a ser
						  filha à esquerda
						  daquela que
						  desceu.*/
      chave = (*no)->chave[pos-1]; 
      (*no)->chave[pos-1]=irma_esq->chave[irma_esq->nregs-1]; 
      NoArvB *filha_esq          = irma_esq->filha[irma_esq->nregs]; 
      RemoveChaveEmNo((*no)->filha[pos-1],(*no)->filha[pos-1]->nregs);
      filha->nregs++;
      filha->filha[0] = filha_esq;
      filha->chave[0] = chave;
      return;
    }
  }
  
  if (pos < (*no)->nregs) { /* existe irmã à direita */ 
    irma_dir = (*no)->filha[pos+1];
    if (irma_dir->nregs > (((*no)->ordem)/2)) { /* A irmã à direita
						  tem chaves para
						  emprestar. A sua
						  primeira chave sobe
						  para o nó pai e a
						  chave do nó pai
						  desce para a filha
						  na posição mais à
						  direita. A filha à
						  esquerda da chave
						  que subiu passa a
						  ser filha à direita
						  daquela que
						  desceu. */
      chave             = (*no)->chave[pos];
      (*no)->chave[pos] = irma_dir->chave[0];
      NoArvB *filha_dir = irma_dir->filha[0];
      RemoveChaveEmNo((*no)->filha[pos+1],0);
      filha->nregs++;
      filha->filha[filha->nregs]   = filha_dir;
      filha->chave[filha->nregs-1] = chave;
      return;
    }    
  }
  
  /* Une a filha com uma das irmãs e a chave do nó pai desce para o nó
     de união, sendo removida depois do nó pai */

  if (pos==0) { /* união com a irmã à direita */
    filha    = (*no)->filha[pos];
    irma_dir = (*no)->filha[pos+1];
    j        = pos;
    filha->chave[filha->nregs]=(*no)->chave[j];
    for(i=(filha->nregs)+1; i<(filha->nregs)+1+(irma_dir->nregs); i++) {
      filha->chave[i] = irma_dir->chave[i-((filha->nregs)+1)];
      filha->filha[i] = irma_dir->filha[i-((filha->nregs)+1)];
    }
    filha->filha[i] = irma_dir->filha[i-((filha->nregs)+1)];
    filha->nregs   += ((irma_dir->nregs)+1);
    free(irma_dir);
  } else  { /* união com a irmã à esquerda */
    irma_esq  = (*no)->filha[pos-1];
    filha     = (*no)->filha[pos];
    j         = pos-1;
    irma_esq->chave[irma_esq->nregs]=(*no)->chave[j];
    for(i=(irma_esq->nregs)+1; i<(irma_esq->nregs)+1+(filha->nregs); i++) {
      irma_esq->chave[i] = filha->chave[i-((irma_esq->nregs)+1)];
      irma_esq->filha[i] = filha->filha[i-((irma_esq->nregs)+1)];
    }
    irma_esq->filha[i] = filha->filha[i-((irma_esq->nregs)+1)];
    irma_esq->nregs   += ((filha->nregs)+1);
    free(filha);
  }

  (*no)->filha[j+1] = (*no)->filha[j];
  
  /* A união de uma filha com uma irmão implica em remoção da chave do
     nó pai, o que pode gerar underflow e se propagar até reduzir a
     altura da árvore.
  */
  
  RemoveChaveEmNo((*no),j); 
}

bool RemoveArvBRec(NoArvB **no, int chave, bool *underflow)
{
  int pos;
  
  /* Verifica se a chave está no nó atual. Se tiver e esse nó for uma
  folha, realiza a remoção. Caso contrário, troca a chave pela
  antecessora e continua o procedimento recursivo para remoção. */
  if (BuscaChaveNoArvB(*no, chave, &pos)) { /* a chave está no nó deste nível */
    if ((*no)->filha[pos]!=NULL) {     /* O nó atual não é uma folha,
					  então a chave precisa ser
					  trocada pela antecessora,
					  reduzindo ao caso de remoção
					  na folha. */
      TrocaChaveComAntecessora(*no, pos);   /* troca a chave pela sua
					       antecessora -- i.e., a
					       chave mais à direita na
					       árvore à esquerda. */
      /* continua o procedimento recursivo para reencontrar e remover
	 a chave do nó folha */
      RemoveArvBRec(&((*no)->filha[pos]), chave, underflow);
      /* trata underflow, se for o caso, após a remoção da chave */
      if (*underflow) TrataNoComMenosChavesQuePermitido(no, pos); 
    } else { /* achou a chave no nó folha, então ela pode ser
		removida. */
      RemoveChaveEmNo(*no, pos);
    }
    /* verifica se a folha ficou em underflow */
    (*underflow) = NoComMenosChavesQuePermitido(*no); 
    return(true); /* remoção bem sucedida */
  } else { /* procura a chave nos nós abaixo */
    if ((*no)->filha[pos] != NULL) {
      if (RemoveArvBRec(&((*no)->filha[pos]), chave, underflow)) {
	/* a chave foi encontrada e removida da folha (raiz da árvore
	   filha). Trata um possível underflow e verifica novamente se
	   ele será propagado para cima (volta da recursão). */
	if (*underflow) TrataNoComMenosChavesQuePermitido(no, pos);
	(*underflow) = NoComMenosChavesQuePermitido(*no);
	return(true);
      } else {
	return(false); /* chego na folha e não achou a chave */
      }
    } else {  /* estamos na raiz e a chave não está neste nível, logo
	         ela não existe. */
      (*underflow) = false;
      return(false);
    }
  }
}

/* -------------------- Funções Públicas ----------------------------------- */

ArvB *CriaNoArvB(int ordem)
{
  NoArvB *no;

  if((ordem > NMAXREGS) || (ordem<2))
    return NULL;

  no = (NoArvB *) calloc(1,sizeof(NoArvB));

  no->ordem = ordem;
  no->nregs = 0;
  memset(no->chave, 0, sizeof(no->chave));    /* zera o vetor de chaves dos registros */
  memset(no->filha, 0, sizeof(no->filha)); /* coloca NULL no vetor de árvores filhas dos registros */

  return(no);
}

bool DestroiArvB(ArvB **arvore)
{
  if ((*arvore) == NULL){
    return(false);
  }

  for(int i=0; i < (NMAXREGS+1); i++)
    if ((*arvore)->filha[i]!=NULL)
      DestroiArvB(&((*arvore)->filha[i]));
  free(*arvore);
  *arvore = NULL;

  return true;
}

bool BuscaChaveArvB(ArvB *arvore, int chave, NoArvB **no, int *pos)
{
  if (arvore == NULL){
    printf("Erro em BuscaChaveArvB: Árvore inexistente\n");
    exit(-1);
  }

  (*no) = arvore;
  /* Busca chave em árvore filha até encontrá-la ou descobrir que a
     chave não está na árvore B */
  while((!ArvBVazia(*no))&&
	(BuscaChaveNoArvB(*no, chave, pos)==false)){
    (*no) = (*no)->filha[*pos];
  }

  /* não encontrou a chave */
  if (ArvBVazia(*no)) 
    return(false);

  /* encontrou a chave e, neste caso, pos e *no contêm o resultado
     desejado */
  return(true);
}

bool InsereArvB(ArvB **arvore, int chave)
{
  bool    overflow=false;
  NoArvB *no=NULL;
  ArvB   *filha_dir=NULL;
  
  if ((*arvore) == NULL){
    printf("Erro em InsereArvB: Árvore inexistente\n");
    exit(-1);
  }
  
  if (InsereArvBRec(arvore, &filha_dir, &chave, &overflow))
    {
      if(overflow) /* aumento da altura da árvore */
	{
	  no           = CriaNoArvB((*arvore)->ordem);
	  no->nregs    = 1;
	  no->filha[0] = (*arvore); /* o nó (raiz anterior) à esquerda da mediana vira a árvore filha da nova raiz */
	  no->filha[1] = filha_dir; /* a filha à direira da mediana vira sua árvore à direira na nova raiz */
	  no->chave[0] = chave;     /* a mediana vira a única chave da nova raiz */ 
	  (*arvore)    = no;        /* o novo nó passa a ser a nova raiz */
	}
      return(true);
    }

  return(false);
}
 

bool RemoveArvB(ArvB **arvore, int chave)
{

  if ((*arvore) == NULL){
    printf("Erro em RemoveArvB: Árvore inexistente\n");
    exit(-1);
  }

  bool underflow=false;
  
  if(RemoveArvBRec(arvore, chave, &underflow)){ /* A chave foi removida */

    /* Se o underflow chegou até a raiz da arvore, entao a raiz antiga
       deve ser eliminada e a nova será a sua única filha, reduzindo
       assim a altura da arvore em 1.
    */
    
    if(underflow) {
      NoArvB *no = *arvore;
      *arvore = (*arvore)->filha[0];
      free(no);
    }

    return(true);
  }

  return(false);
}

void ImprimeArvBPreOrdem(ArvB *arv, int nivel) {
  int i;

  if(arv != NULL) {
    printf("nivel %02d\n", nivel);
    for(i = 0; i < arv->nregs; i++) {
      printf("%03d ", arv->chave[i]);
    }
    printf("\n");
    for(i = 0; i < arv->nregs+1; i++) {
      ImprimeArvBPreOrdem(arv->filha[i], nivel + 1);
    }
  }
}

void ImprimeArvB(ArvB *ab, int nivel, int filha)
{
  int n;

  if (ab != NULL) {
    for (n=1; n<nivel; n++)
      printf("     ");
    printf("%d)", filha);
    printf("[");
    for (n=0; n < ab->nregs; n++)
      printf(" %d",ab->chave[n]);
    printf("]\n");
    for (n=0; n <= ab->nregs; n++)
      ImprimeArvB(ab->filha[n], nivel+1, n);
  }
}










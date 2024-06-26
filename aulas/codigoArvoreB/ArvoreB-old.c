#include "ArvoreB.h"


/*
typedef struct arvb {  
  int ordem; 
  int elems; 
  int info[TAMMAX]; 
  struct arvb *filhos[TAMMAX+1]; 
} ArvB;
*/

ArvB *ArvBCria(int ordem)
/* Cria uma arvore B com a ordem passada pelo parametro. Devolve NULL
   Caso a ordem seja maior do que o tamanho maximo especificado, ou 
   se deu algum pau de memoria
*/
{
  ArvB *temp;
  if((ordem>TAMMAX)||(ordem<2))
    return NULL;
  if ((temp = (ArvB *) calloc(1,sizeof(ArvB)))==NULL)
    return NULL;
  temp->ordem = ordem;
  temp->elems = 0;
  memset(temp->info, 0, sizeof(temp->info)); /* zera o vetor todo de uma vez*/
  memset(temp->filhos, 0, sizeof(temp->filhos));
  return(temp);
}

int ArvBDestroi(ArvB **arvore)
/* Destroi a Arvore B. O apontador arvore deve retornar Nulo.
   int retorna 1 se tudo deu certo, ou 0 se deu algum tipo de pau.
*/
{
  int i;
  if (*arvore == NULL)
    return 0;
  else
    for(i=0; i<(TAMMAX+1); i++)
      if ((*arvore)->filhos[i]!=NULL)
	ArvBDestroi(&((*arvore)->filhos[i]));
  free(*arvore);
  *arvore = NULL;
  return 1;
}

/* int ArvBInsereRec(ArvB **arvore, ArvB **aux, int *valor, int *quebrou) */
/* { */
/*   int i=0, j=0; */
/*   if (*arvore==NULL) { */
/*       (*quebrou) = 1; */
/*       (*aux) = NULL; */
/*       return 1; */
/*   } else { */
/*     while((((*arvore)->info[i])<(*valor))&&(i<(*arvore)->elems)) */
/*       i++; */
/*     if ((i<(*arvore)->elems)&&((*valor)==(*arvore)->info[i])) { */
/*       /\* Elemento encontrado na arvore, ignora inserção *\/ */
/*       (*quebrou) = 0; */
/*       return 0; */
/*     } else { */
/*       if (ArvBInsereRec(&((*arvore)->filhos[i]),aux,valor,quebrou)) { */
/* 	/\* Insere recursivamente o elemento no nó apropriado *\/ */
/* 	if (*quebrou) { */
/* 	  /\* O nó filho foi quebrado, então precisamos inserir a chave do filho no lugar de i (retornada em *valor)  */
/* 	     e verificar se o nó atual (pai) deve ser quebrado também *\/ */
	  
/* 	  for (j = (*arvore)->elems; j > i; j--) { */
/* 	    (*arvore)->info[j] = (*arvore)->info[j-1]; */
/* 	    (*arvore)->filhos[j+1] = (*arvore)->filhos[j]; */
/* 	  } */
/* 	  /\* Afasta todo mundo acima da posicao i-1 para info, */
/* 	     e i para filhos, uma casa para a direita *\/ */
/* 	  (*arvore)->info[i] = (*valor); */
/* 	  (*arvore)->filhos[i+1] = (*aux); */
/* 	  (*arvore)->elems++; */
/* 	  /\* Coloca os novos membros no local correto *\/ */
/* 	  if ((*arvore)->elems <= (*arvore)->ordem) */
/* 	      (*quebrou) = 0; */
/* 	  /\* Verifica se houve estouro de folha *\/ */
/* 	  else { */
/* 	    /\* Arvore arrebentada.*\/ */
/* 	    (*aux) = ArvBCria((*arvore)->ordem); */
/* 	    i = (((*arvore)->ordem)+1)/2; */
/* 	    (*valor) = (*arvore)->info[i]; */
/* 	    (*arvore)->elems = i; */
/* 	    i++; */
/* 	    /\* Salvou o elemento do meio *\/ */
/* 	    for (;i<((*arvore)->ordem+1);i++) { */
/* 	      (*aux)->info[i-((((*arvore)->ordem+1)/2)+1)] = (*arvore)->info[i]; */
/* 	      (*aux)->filhos[i-((((*arvore)->ordem+1)/2)+1)] = (*arvore)->filhos[i]; */
/* 	      (*arvore)->filhos[i] = NULL; */
/* 	    } */
/* 	    /\* Copiando os elementos para o no auxiliar *\/ */
/* 	    (*aux)->filhos[i-(((((*arvore)->ordem+1)/2))+1)] = (*arvore)->filhos[i]; */
/* 	    (*arvore)->filhos[i] = NULL; */
/* 	    /\* Copiando o filho a mais *\/ */
/* 	    (*aux)->elems = ((*aux)->ordem)/2; */
/* 	    (*quebrou) = 1; */
/* 	  } */
/* 	} */
/* 	return 1; */
/*       } */
/*       return 0; */
/*     } */
/*   } */
/* } */

/* BuscaChaveNo recebe um no' da arvore B e procura a chave neste no';
Duas coisas podem acontecer: (1) a chave esta' neste no' (2) a chave nao
est'a neste no.  No primeiro caso, a funcao retorna 1 e posicao recebe o
indice da chave; no segundo caso, a funcao retorna 0 e posicao recebe o
indice do filho onde a chave se encontra */
 
int BuscaChaveNo(ArvB *arv, int chave, int *posicao)
{
  int i=0;
  while((arv->info[i]<chave)&&(i<arv->elems))
	i++;
  (*posicao) = i;
  if ((arv->info[i] == chave)&&(i<arv->elems))
      return 1;
  else
      return 0;
}

/* InsereNovoValorEFilhoNo: Coloca os novos membros no local correto */
void InsereNovoValorEFilhoNo(ArvB *arvore, ArvB *aux, int valor, int pos) {
  int j;
  for (j = arvore->elems; j > pos; j--) {
    arvore->info[j] = arvore->info[j-1];
    arvore->filhos[j+1] = arvore->filhos[j];
  }
  /* Afasta todo mundo acima da posicao pos-1 para info,
     e pos para filhos, uma casa para a direita */
  arvore->info[pos] = valor;
  arvore->filhos[pos+1] = aux;
  arvore->elems++;
}

/* VerificaOverflow: retorna 1 se o no' passado esta' em overflow,
e zero caso contrario */
 
int VerificaOverflow(ArvB *arv)
{
  return arv->elems > arv->ordem;
}

/* VerificaUnderflow: retorna 1 se o no' passado esta' em underflow,
e zero caso contrario */
 
int VerificaUnderflow(ArvB *arv)
{
  return(arv->elems<(arv->ordem/2));
}

/* TrataOverflow: divide o no cheio e retorna a chave mediana */
int TrataOverflow(ArvB **arvore, ArvB **aux) {
  int i, valor;

  (*aux) = ArvBCria((*arvore)->ordem);
  i = (((*arvore)->ordem)+1)/2;
  valor = (*arvore)->info[i];
  (*arvore)->elems = i;
  i++;
  /* Salvou o elemento do meio */
  for (;i<((*arvore)->ordem+1);i++) {
    (*aux)->info[i-((((*arvore)->ordem+1)/2)+1)] = (*arvore)->info[i];
    (*aux)->filhos[i-((((*arvore)->ordem+1)/2)+1)] = (*arvore)->filhos[i];
    (*arvore)->filhos[i] = NULL;
  }
  /* Copiando os elementos para o no auxiliar */
  (*aux)->filhos[i-(((((*arvore)->ordem+1)/2))+1)] = (*arvore)->filhos[i];
  (*arvore)->filhos[i] = NULL;
  /* Copiando o filho a mais */
  (*aux)->elems = ((*aux)->ordem)/2;

  return valor;
}

int ArvBInsereRec(ArvB **arvore, ArvB **aux, int *valor, int *quebrou)
{
  int i=0, j=0;
  if (*arvore==NULL) {
      (*quebrou) = 1;
      (*aux) = NULL;
      return 1;
  } else {
    if(BuscaChaveNo(*arvore, *valor, &i)) {
      /* Elemento encontrado na arvore, ignora inserção */
      (*quebrou) = 0;
      return 0;
    } else {
      if (ArvBInsereRec(&((*arvore)->filhos[i]),aux,valor,quebrou)) {
	/* Insere recursivamente o elemento no nó apropriado */
	if (*quebrou) {
	  /* O nó filho foi quebrado, então precisamos inserir a chave 
	     do filho no lugar de i (retornada em *valor) e verificar 
	     se o nó atual (pai) deve ser quebrado também */
	  
	  InsereNovoValorEFilhoNo(*arvore, *aux, *valor, i);

	  if (!VerificaOverflow(*arvore)) {
	    (*quebrou) = 0;
	    /* Verifica se houve estouro de folha */
	  } else {
	    /* Arvore arrebentada.*/

	    (*valor) = TrataOverflow(arvore, aux);

	    (*quebrou) = 1;
	  }
	}
	return 1;
      }
      return 0;
    }
  }
}


int ArvBInsere(ArvB **arvore, int valor)
/* Insere o elemento "Valor" na arvore "arvore". Devolve 1 se 
   deu tudo certo, devolve 0 se deu pau em alguma coisa.
   (por exemplo, se a arvore nao existe, ou se esse valor ja 
   existe na arvore).
*/
{
  int quebrou=0;
  ArvB *temp1=NULL, *temp2=NULL;
  if ((*arvore) == NULL)
    return 0;
  if (ArvBInsereRec(&(*arvore), &temp1, &valor, &quebrou))
    {
      if(quebrou)
	{
	  temp2 = ArvBCria((*arvore)->ordem);
	  temp2->elems = 1;
	  temp2->filhos[0] = (*arvore);
	  temp2->filhos[1] = temp1;
	  temp2->info[0] = valor;
	  (*arvore)=temp2;
	}
      return 1;
    }
  else
    return 0;
}

int ArvBBusca(ArvB *arvore, int valor)
/* Busca o valor "Valor" na arvore "arvore". 
   A funcao deve retornar 0 se o valor nao existir na arvore ou se 
   ocorrer algum tipo de Pau. Caso o valor esteja na arvore, a funcao
   deve retornar o nivel no qual o valor se encontra (a raiz 
   possui nivel 1
*/
{
  int nivel = 1, i = 0;
  ArvB *aux;
  aux = arvore;
  if (aux == NULL)
    return 0;
  while(nivel) {
    while((aux->info[i]<valor)&&(i<aux->elems))
      i++;
    /*procura o primeiro elemento maior que o valor, ou a posicao depois
      da arvore*/
    if ((aux->info[i] == valor)&&(i<aux->elems))
      return(nivel);
    /*verifica se achou o elemento (fora da arvore nao vale*/
    else {
      if (aux->filhos[i] != NULL) {
	aux = aux->filhos[i];
	i = 0;
	nivel++;
      } else
	return 0;
      /* se nao achou o elemento neste nivel, tenta descer um nivel. 
	 se nao conseguir, retorna 0 que faiou.
      */
    }
  }
  return 0;
}
  
  

/* RemoveChaveNo recebe um no de arvore B e uma posicao; remove a chave
nesta posicao, transladando de uma posicao pra tras as chaves e filhos
posteriores.  Diminui numero de chaves do no */
 
void RemoveChaveNo(ArvB *arv, int posicao)
{
  int i;
  for(i=posicao; i<arv->elems; i++)
    {
      arv->info[i] = arv->info[i+1];
      arv->filhos[i] = arv->filhos[i+1];
    }
  arv->filhos[i] = arv->filhos[i+1];
  arv->filhos[i+1] = NULL;
  arv->elems--;
}


/* TrataUnderflow: esta rotina e' chamada para tratar um caso de underflow
num filho;  recebe um no de arvore B e uma posicao de filho, que
esta' com underflow, isto e', com menos que \floor{b/2} chaves.  O que ela
faz: verifica se o filho `a esquerda pode doar uma chave, caso nao consiga
tenta o filho `a direita, caso nao consiga junta o filho em underflow com
um de seus irmaos (tenta primeiro o `a esquerda, se nao existir pega o `a
direita), e com uma chave de si mesmo para formar um novo no, e neste
caso chama RemoveChaveNo para transladar o que precisa. O no pai pode ficar
com underflow, o que e tratado na volta da recursao ate a raiz. Se a raiz
raiz ficar com undeflow, entao o problema 'e tratado fora da recursao de 
modo que a arvore diminui de altura.*/
 

void TrataUnderflow(ArvB **arv, int posicao)
{
  int i,j;
  ArvB *aux=NULL, *aux2=NULL;
  /* verifica se o filho a esquerda pode doar um no, e faz isso se puder */
  aux2 = (*arv)->filhos[posicao];
  if (posicao > 0) {
    aux = (*arv)->filhos[posicao-1];
    if(aux->elems > (((*arv)->ordem)/2)) {
      i = (*arv)->info[posicao-1];
      (*arv)->info[posicao-1]=aux->info[aux->elems-1];
      aux->elems--;
      aux = aux->filhos[aux->elems+1];
      (*arv)->filhos[posicao-1]->filhos[(*arv)->filhos[posicao-1]->elems+1] = NULL;
      for (j = aux2->elems; j > 0; j--) {
	aux2->info[j] = aux2->info[j-1];
	aux2->filhos[j+1] = aux2->filhos[j];
      }
      aux2->filhos[j+1] = aux2->filhos[j];
      aux2->elems++;
      aux2->filhos[0] = aux;
      aux2->info[0] = i;
      return;
    }
  }
  /* verifica se o filho a direita pode doar um no, e faz isso se puder */
  aux = (*arv)->filhos[posicao+1];
  if ((posicao<(*arv)->elems)&&(aux->elems > (((*arv)->ordem)/2))) {
    i = (*arv)->info[posicao];
    (*arv)->info[posicao]=aux->info[0];
    aux = aux->filhos[0];
    RemoveChaveNo((*arv)->filhos[posicao+1],0);
    aux2->elems++;
    aux2->filhos[aux2->elems] = aux;
    aux2->info[aux2->elems-1] = i;
    return;
  }    
  /* trata para tentar unir dois irmaos */
  if (posicao==0) {
    aux = (*arv)->filhos[posicao];
    aux2 = (*arv)->filhos[posicao+1];
    j = posicao;
  } else  {
    aux = (*arv)->filhos[posicao-1];
    aux2 = (*arv)->filhos[posicao];
    j = posicao-1;
  }
  /* arvore resultante tem que ser posta no filho j+1 para chamar 
     depois o removeno
  */
  aux->info[aux->elems]=(*arv)->info[j];
  for(i=(aux->elems)+1; i<(aux->elems)+1+(aux2->elems); i++) {
    aux->info[i] = aux2->info[i-((aux->elems)+1)];
    aux->filhos[i] = aux2->filhos[i-((aux->elems)+1)];
  }
  aux->filhos[i] = aux2->filhos[i-((aux->elems)+1)];
  aux->elems += ((aux2->elems)+1);
  free(aux2);
  (*arv)->filhos[j+1] = (*arv)->filhos[j];

  /* Apos a remocao da chave do pai, ele pode ficar com underflow, o
     que sera tratado recursivamente ate a raiz. Chegando na raiz, se
     ela tambem ficar com underflow o problema sera consertado fora da
     recursao de modo a reduzir a altura da arvore.
  */
  RemoveChaveNo((*arv),j); 
}
   


/* TrocaChaveAnterior: troca uma chave com a sua anterior, que
necessariamente esta  numa folha; recebe um no de arvore B e uma posicao
de chave. */
 
void TrocaChaveAnterior(ArvB *arv, int posicao)
{
  ArvB *aux;
  int i;
  aux = arv->filhos[posicao];
  while(aux->filhos[aux->elems]!=NULL)
    aux = aux->filhos[aux->elems];
  i = arv->info[posicao];
  arv->info[posicao] = aux->info[aux->elems-1];
  aux->info[aux->elems-1] = i;
  return;
}


/* ArvBRemoveRec: recursiva; faz o trabalho necessario para a remocao mas
restringe-se a um nivel.  Recebe um no de arvore B e uma chave a remover;
Cuida de localizar a chave neste no, chamar-se recursivamente para cuidar
dos niveis inferiores, e arrumar a casa neste nive em caso de underflow de
filho; Retorna um booleanos: underflow, que indica se o no corrente ficou 
em underflow depois da arrumacao. Alem disso, a funcao retorna 1 se 
a chave existia na arvore, ou 0 se nao existia.  Obs: Caso a chave esteja 
neste nivel mas o nivel nao e' o ultimo (ou seja, a chave nao estava 
numa folha), troca a chave com a chave imediatamente anterior, que
necessariamente estara' numa folha, para poder prosseguir com o usual.
So' se remove chave em folha neste esquema.
*/
 
int ArvBRemoveRec(ArvB **arv, int chave, int *underflow) {
  int pos;
  /* Primeiro, procura onde esta a chave */
   if (BuscaChaveNo(*arv, chave, &pos)) {
    /* a chave esta neste nivel */
    if ((*arv)->filhos[pos]!=NULL) {   /* Nao estamos na folha */
      TrocaChaveAnterior(*arv, pos);   /* manda a chave para baixo */
      ArvBRemoveRec(&((*arv)->filhos[pos]), chave, underflow);
      if (*underflow) TrataUnderflow(arv, pos);
    } else {
      RemoveChaveNo(*arv, pos);
    }
    (*underflow) = VerificaUnderflow(*arv);
    return 1;
  } else { /* a chave nao esta neste nivel */
    if ((*arv)->filhos[pos]!=NULL) {
      if (ArvBRemoveRec(&((*arv)->filhos[pos]), chave, underflow)) {
	/* existe o no abaixo */
	if (*underflow) TrataUnderflow(arv, pos);
	(*underflow) = VerificaUnderflow(*arv);
	return 1;
      } else
	return 0;/* nao existe o no abaixo */
    } else {  /* estamos na raiz e a chave nao esta neste nivel, 
	         logo, ela nao existe */
      (*underflow) = 0;
      return 0;
    }
  }
}


int ArvBRemove(ArvB **arvore, int valor)
/* Remove o valor "valor" da arvore "arvore".
   retorna 0 caso o valor nao exista, ou caso de algum pau
   (como passarem uma arvore nula).
   retorna 1 caso tenha tido sucesso.
*/
{
  ArvB *aux = NULL;
  int removido = 0, underflow=0;
  if (arvore!=NULL)
    removido = ArvBRemoveRec(arvore, valor, &underflow);

  /* Se a chave foi removida e o underflow chegou ate a raiz da arvore, entao a 
     raiz antiga deve ser eliminada e a nova deve apontar para seu filho unico,
     reduzindo assim a altura da arvore em 1.
  */
  if(removido && underflow) {
    aux = *arvore;
    *arvore = (*arvore)->filhos[0];
    free(aux);
  }

  return removido;
}

void ArvBImprimePreOrdem(ArvB *arv, int nivel) {
  int i;

  if(arv != NULL) {
    printf("nivel %02d\n", nivel);
    for(i = 0; i < arv->elems; i++) {
      printf("%03d ", arv->info[i]);
    }
    printf("\n");
    for(i = 0; i < arv->elems+1; i++) {
      ArvBImprimePreOrdem(arv->filhos[i], nivel + 1);
    }
  }
}

void ArvBImprime(ArvB *ab, int nivel, int filho)
{
  int n;

  if (ab != NULL) {
    for (n=1; n<nivel; n++)
      printf("     ");
    printf("%d)", filho);
    printf("[");
    for (n=0; n < ab->elems; n++)
      printf(" %d",ab->info[n]);
    printf("]\n");
    for (n=0; n <= ab->elems; n++)
      ArvBImprime(ab->filhos[n], nivel+1, n);
  }
}










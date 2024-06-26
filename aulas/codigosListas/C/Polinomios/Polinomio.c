#include "Polinomio.h"

Polinomio *LePolinomio(char *arq)
{
  FILE *fp=fopen(arq,"r");
  Polinomio *P=NULL;
  int i, ntermos, expo;
  float coef;

  fscanf(fp,"%d\n",&ntermos);
  for (i=0; i < ntermos; i++) {
    fscanf(fp,"%f %d\n",&coef,&expo);
    InsereTermoPolinomio(&P,coef,expo);
  }
  fclose(fp);

  return(P);
}

bool BuscaTermoPolinomio(Polinomio *P, int expo, NoPolinomio **termo, NoPolinomio **termo_ant)
{
  *termo_ant = NULL;
  *termo     = P;

  while (((*termo) != NULL)&&((*termo)->expo > expo)){
    (*termo_ant) = (*termo);
    (*termo)     = (*termo)->prox;
  }

  
  if (((*termo)!=NULL)&&((*termo)->expo==expo))
    return(true);

  return(false);
}

NoPolinomio *CriaNoPolinomio(float coef, float expo)
{
  NoPolinomio *termo = (NoPolinomio *)calloc(1,sizeof(NoPolinomio));
  termo->coef = coef;    
  termo->expo = expo;
  termo->prox = NULL;
  return(termo);
}

void InsereTermoPolinomio(Polinomio **P, float coef, int expo)
{
  NoPolinomio *termo, *termo_ant;
  
  if (BuscaTermoPolinomio(*P, expo, &termo, &termo_ant)){ /* Atualiza
						coeficiente se termo
						ja existe */
    printf("Atualizando coeficiente %.2f x^%d para %.2f x^%d\n",termo->coef,expo,coef,expo);
    termo->coef = coef;
  } else {

    /* cria novo termo para o polinomio */

    termo = CriaNoPolinomio(coef,expo);
    if (termo_ant != NULL){ /* O polinomio ja tem termos e a insercao
			       sera no meio ou final da lista */
      termo->prox     = termo_ant->prox;
      termo_ant->prox = termo;
    } else { 
      if (*P != NULL) { /* O polinomio ja tem termos e a insercao sera
			   no inicio da lista */	
	termo->prox = *P;
      }
      *P = termo;
    }

    // ImprimePolinomio(*P);
  }
}

void       DestroiPolinomio(Polinomio **P)
{
  NoPolinomio *p=*P, *q;

    while (p != NULL){
      q = p->prox;
      free(p);
      p = q;
    }
    *P = NULL;
}

void       ImprimePolinomio(Polinomio *P)
{
  Polinomio *p=P;

  while (p!=NULL) {
    if (p->expo != 0){
      if (p->coef != 0.0){
	if (p->coef > 0.0)
	  printf("+ %.2fx^%d ",p->coef,p->expo);
	else
	  printf("- %.2fx^%d ",-p->coef,p->expo);
      }
    } else {
      if (p->coef != 0.0){
	if (p->coef > 0.0)
	  printf("+ %.2f ",p->coef);
	else
	  printf("- %.2f ",-p->coef);
      }
    }
    p = p->prox;
  }
  printf("\n");

}

/* Calcula o numero de termos */

int  NumeroTermosPolinomio(Polinomio *P)
{
  Polinomio *p=P;
  int numero_de_termos = 0;

  while (p!=NULL) {
    numero_de_termos++;
    p = p->prox;
  }
  
  return(numero_de_termos);
}

/* Grava polinomio */

void  GravaPolinomio(Polinomio *P, char *nomearq)
{
  Polinomio *p=P;
  FILE *fp = fopen(nomearq,"w");
  int numero_de_termos = NumeroTermosPolinomio(P);

  fprintf(fp,"%d\n",numero_de_termos);
  while (p!=NULL) {
    fprintf(fp,"%5.2f %d\n",p->coef,p->expo); 
    p = p->prox;
  }
  
  fclose(fp);
}


/* Parecida com uniao de listas */

Polinomio *SomaPolinomios(Polinomio *P1, Polinomio *P2)
{
  Polinomio *P3=NULL, *P=P1, *Q=P2;

  while ((P != NULL)&&(Q != NULL)) {
    if (P->expo > Q->expo){
      InsereTermoPolinomio(&P3,P->coef,P->expo);
      P = P->prox;
    } else {
      if (P->expo < Q->expo){
	InsereTermoPolinomio(&P3,Q->coef,Q->expo);
	Q = Q->prox;
      } else { /* soma */
	InsereTermoPolinomio(&P3,P->coef+Q->coef,P->expo);
	P = P->prox;
	Q = Q->prox;
      }
    }
  }

  while (P != NULL) {
    InsereTermoPolinomio(&P3,P->coef,P->expo);
    P = P->prox;
  }

  while (Q != NULL) {
    InsereTermoPolinomio(&P3,Q->coef,Q->expo);
    Q = Q->prox;
  }

  return(P3);
}

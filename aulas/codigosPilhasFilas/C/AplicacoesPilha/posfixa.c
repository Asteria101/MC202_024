#include "PilhaDinamica.h"

/* Entre com uma expressão matemática em notação in-fixa. Por exemplo: 

   (2+3)*5

   O programa deverá verificar se a expressão está com os parênteses
   balanceados, converter para pós-fixa 23+5* e executar a expressão
   pós-fixa.

   Para compilar: gcc posfixa.c PilhaDinamica.c -o posfixa -lm
   Para executar: posfixa "(2+3)*5"

*/


bool Balanceada(char *expressao)
{
  Pilha *pilha = CriaPilha();
  int    n     = strlen(expressao);

  /* Empilha '(' e desempilha '(' à medida que chega ')' na entrada */
  
  for (int i=0; i < n; i++) {
    switch(expressao[i]){ 
    case '(': 
      EmpilhaCaracter(&pilha,expressao[i]);
      break;
    case ')':
      if (PilhaVazia(pilha))
	return(false);     
      DesempilhaCaracter(&pilha);
      break;
    }
  }

  if (PilhaVazia(pilha))
    return(true);
  else{
    DestroiPilha(&pilha);
    return(false);
  }
}

float ExecutaPosfixa(char *expressao)
{
  Pilha *pilha = CriaPilha();
  int    n     = strlen(expressao);
  float a, b, res;

  /* Dígitos são empilhados e à medida que chegam os operadores, eles
     são desempilhados e a operação é executada. */
  
  for (int i=0; i < n; i++) {
    if (('0' <= expressao[i])&&(expressao[i] <= '9')){ /* dígito de 0-9 */
      EmpilhaValor(&pilha,(float)expressao[i]-48);
    } else {
      switch(expressao[i]) {
      case '+':
	 a   = DesempilhaValor(&pilha);
	 b   = DesempilhaValor(&pilha);
	 res = a + b;
	 EmpilhaValor(&pilha,res);
	break;
      case '-':
	 a   = DesempilhaValor(&pilha);
	 b   = DesempilhaValor(&pilha);
	 res = b - a;
	EmpilhaValor(&pilha,res);
	break;
      case '*':
	 a   = DesempilhaValor(&pilha);
	 b   = DesempilhaValor(&pilha);
	 res = a * b;
	 EmpilhaValor(&pilha,res);
	break;
      case '/':
	 a   = DesempilhaValor(&pilha);
	 b   = DesempilhaValor(&pilha);
	if (a != 0){
	   res = b / a;
	   EmpilhaValor(&pilha,res);
	}else{
	  printf("Divisão por zero\n");
	  exit(1);
	}	    
	break;
      case '^':
	 a   = DesempilhaValor(&pilha);
	 b   = DesempilhaValor(&pilha);
	 res = pow(b,a);
	 EmpilhaValor(&pilha,res);
	break;
      default:
	printf("Expressão inválida\n");
	exit(1);	  
      }
    }
  }
  
  return(DesempilhaValor(&pilha));
}

char *InFixaParaPosFixa(char *expressao)
{
  Pilha *pilha  = CriaPilha();
  int    n      = strlen(expressao), j = 0;
  char  *posfixa = (char *)calloc(n,sizeof(char)), x;

  /* Empilha um primeiro '(' apenas para garantir que a pilha nunca
     estará vazia. Os caracteres '(' são empilhados e a cada ')' na
     entrada, a pilha é esvaziada e os operadores repassados à saída
     até o '(' correspondente. Os dígitos são repassados diretamente
     para a saída, mas os operadores são empilhados para aguardar
     operadores de menor prioridade na entrada. Dado um operador de
     entrada, a pilha é esvaziada com os operadores sendo repassados
     para a saída enquando a prioridade deles for maior do que a do
     operador de entrada. Depois este deve ser empilhado. Para casos
     onde "-" é unária, por exemplo (-3), melhor escrever (0-3) já que
     a "-" é tratada na execução como operador binário. */
  
  EmpilhaCaracter(&pilha,'(');

  for (int i=0; i < n; i++) {
    if (('0' <= expressao[i])&&(expressao[i] <= '9')){ /* dígito de 0-9 */
      posfixa[j]=expressao[i]; j++;
    } else {
      switch(expressao[i]) {
      case '(':
	EmpilhaCaracter(&pilha,expressao[i]);
	break;
      case ')':
	x   = DesempilhaCaracter(&pilha);
	while (x != '('){
	  posfixa[j]=x; j++;
	  x   = DesempilhaCaracter(&pilha);
	}
	break;
      case '+':
	do {
	  x   = DesempilhaCaracter(&pilha);
	  if ((x == '*') || (x == '/') || (x == '+') || (x == '-') || (x == '^')){ 
	    posfixa[j]=x; j++;
	  } else {
	    EmpilhaCaracter(&pilha,x);
	  }
	} while(x != '(');
	EmpilhaCaracter(&pilha,expressao[i]);
	break;
      case '-':
	do {
	  x   = DesempilhaCaracter(&pilha);
	  if ((x == '*') || (x == '/') || (x == '+') || (x == '-') || (x == '^')){ 
	    posfixa[j]=x; j++;
	  } else {
	    EmpilhaCaracter(&pilha,x);
	  }
	} while(x != '(');
	EmpilhaCaracter(&pilha,expressao[i]);
	break;
      case '*':
	do {
	  x   = DesempilhaCaracter(&pilha);
	  if ((x == '*') || (x == '/') || (x == '^')){ 
	    posfixa[j]=x; j++;
	  } else {
	    EmpilhaCaracter(&pilha,x);
	  }
	} while((x != '(')&&(x != '+')&&(x != '-'));
	EmpilhaCaracter(&pilha,expressao[i]);
	break;
      case '/':
	do {
	  x   = DesempilhaCaracter(&pilha);
	  if ((x == '*') || (x == '/') || (x == '^')){ 
	    posfixa[j]=x; j++;
	  } else {
	    EmpilhaCaracter(&pilha,x);
	  }
	} while((x != '(')&&(x != '+')&&(x != '-'));
	EmpilhaCaracter(&pilha,expressao[i]);
	break;
      case '^':
	EmpilhaCaracter(&pilha,expressao[i]);
	break;
      default:
	printf("Expressão inválida\n");
	exit(1);	  
      }
    }
  }
  while (!PilhaVazia(pilha)){
    x   = DesempilhaCaracter(&pilha);
    if (x != '(') {
      posfixa[j]=x; j++;
    }
  }
  posfixa[j]='\0';
  
  return(posfixa);
}

int main(int argc, char **argv)
{

  if (argc != 2) {
    printf("%s <expressão matemática com parênteses>\n",argv[0]);
    exit(1);
  }

  if (Balanceada(argv[1])){
      char *posfix = InFixaParaPosFixa(argv[1]);  
      printf("Posfixa: %s, resultado: %f\n",posfix,ExecutaPosfixa(posfix));
      free(posfix);
    } else {
      printf("Expressão desbalanceada.\n");
    }
    
  return(0);
}

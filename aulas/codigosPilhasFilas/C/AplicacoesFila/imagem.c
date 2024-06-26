#include "imagem.h"

/* -------------- funções privadas --------------------------- */

/* Gera número aleatório em [min,max] */

int NumeroAleatorio(int min, int max) {
  double d;
  d = ((double) rand()) / (double) RAND_MAX;
  return((int)(min + d * (max - min)));
}

/* --------------- funções públicas ----------------------------*/


Imagem *CriaImagem(int nx, int ny, int nbandas)
{
  Imagem *img = (Imagem *)calloc(1,sizeof(Imagem));

  img->nx = nx; 
  img->ny = ny; 
  img->nbandas = nbandas; 
  img->banda = (int ***)calloc(nbandas,sizeof(int **));
  for (int b=0; b < nbandas; b++){
    img->banda[b] = (int **)calloc(ny,sizeof(int *));
    for (int y=0; y < ny; y++)
      img->banda[b][y] = (int *)calloc(nx,sizeof(int));
  }
  return(img);
}

void   *DestroiImagem(Imagem **img)
{
  Imagem *aux = *img;

  if (aux != NULL) {
    for (int b=0; b < aux->nbandas; b++){
      for (int y=0; y < aux->ny; y++)
	free(aux->banda[b][y]);
      free(aux->banda[b]);
    }
    free(aux);
    (*img)=NULL;
  }
}

Imagem *LeImagem(char *nome_img)
{
  FILE *fp=fopen(nome_img,"r");
  Imagem *img = NULL;
  char tipo[10];
  int  nx, ny, nbandas, max;
  
  /* Lê o cabeçário ASCII */
  fscanf(fp,"%s\n",tipo);
  fscanf(fp,"%d %d\n",&nx,&ny);
  fscanf(fp,"%d\n",&max);
  
  /* Lê os dados binários dos pixels */
  if (strcmp(tipo,"P5")==0){
    nbandas = 1;
  } else {
    if (strcmp(tipo,"P6")==0){
      nbandas = 3;
    } else {
      printf("Formato desconhecido de imagem\n");
      exit(-1);
    }
  }
  
  int size = nx*ny*nbandas;
  unsigned char *dados = (unsigned char *)calloc(size,sizeof(unsigned char));
  fread(dados,sizeof(unsigned char),size,fp);
  
  /* Copia para a imagem */
  img = CriaImagem(nx,ny,nbandas);
  if (nbandas == 3){
    for (int p=0, q=0; p < size; p+=3, q++){
      int x = q%nx, y=q/nx;    
      img->banda[0][y][x] = (int)dados[p];
      img->banda[1][y][x] = (int)dados[p+1];
      img->banda[2][y][x] = (int)dados[p+2];
    }
  } else { /* nbandas == 1 */
    for (int p=0; p < size; p++){
      int x = p%nx, y=p/nx;    
      img->banda[0][y][x] = (int)dados[p];
    }
  }
    
  fclose(fp);
  free(dados);
  return(img);
}

void  GravaImagem(Imagem *img, char *nome_img)
{
  FILE *fp=fopen(nome_img,"w");
  
  /* Grava o cabeçário ASCII */
  if (img->nbandas==3){
    fprintf(fp,"P6\n");
  } else {
    if (img->nbandas==1){
      fprintf(fp,"P5\n");
    } else {
      printf("Número de bandas %d diferente de 1 e 3 \n",img->nbandas);
      exit(-1);
    }
  }

  fprintf(fp,"%d %d\n",img->nx,img->ny);
  fprintf(fp,"255\n");
    
  /* Copia a imagem para o vetor de dados */
  int size = img->nx*img->ny*img->nbandas;
  unsigned char *dados = (unsigned char *)calloc(size,sizeof(unsigned char));
  if (img->nbandas==3){
    for (int p=0, q=0; p < size; p+=3, q++){
      int x = q%img->nx, y=q/img->nx;    
      dados[p]   = (unsigned char)img->banda[0][y][x];
      dados[p+1] = (unsigned char)img->banda[1][y][x];
      dados[p+2] = (unsigned char)img->banda[2][y][x];
    }
  } else { /* nbandas é 1 */
    for (int p=0; p < size; p++){
      int x = p%img->nx, y=p/img->nx;    
      dados[p]   = (unsigned char)img->banda[0][y][x];
    }
  }
  
  /* Grava os dados binários dos pixels */
  fwrite(dados,sizeof(unsigned char),size,fp);
  fclose(fp);
}

Imagem *RotulaComponentes(Imagem *img, Adjacencia *adj)
{
  Imagem *rot = CriaImagem(img->nx,img->ny,1);
  Fila *Q     = CriaFila(img->nx*img->ny);
  int rotulo  = 1;
  
  for (int yr=0; yr < img->ny; yr++){
    for (int xr=0; xr < img->nx; xr++){
      if ((img->banda[0][yr][xr]!=0)&&(rot->banda[0][yr][xr]==0)){ /* componente (foreground) ainda não rotulado */
	int r = xr + yr * img->nx;
	rot->banda[0][yr][xr] = rotulo; /* atribui rótulo para propagação */
	InsereFila(Q,r); /* insere primeiro pixel (raiz) do componente na fila */
	printf("rotulo %d\n",rotulo);
	while (!FilaVazia(Q)) {
	  int p;
	  RemoveFila(Q,&p); /* remove pixel p de Q */
	  int xp = p % img->nx; int yp = p / img->nx;
	  for (int i=0; i < adj->nadj; i++) { /* para cada adjacente q de p */
	    int xq = xp + adj->dx[i]; int yq = yp + adj->dy[i];
	    if ((xq >= 0)&&(xq < img->nx)&&(yq >= 0)&&(yq < img->ny)){ /* se q estiver no domínio da imagem */
	      if ((img->banda[0][yq][xq]!=0)&&(rot->banda[0][yq][xq]==0)){ /* se q pertence a um componente e ainda não está rotulado */
		rot->banda[0][yq][xq] = rot->banda[0][yp][xp]; /* propaga rótulo de p para q. Este é o mesmo rótulo de r, que também está na variável rotulo. */
		int q = xq + yq * img->nx; 
		InsereFila(Q,q); /* insere pixel q na fila */
	      }
	    }
	  }
	}
	rotulo++;
      }
    }
  }

  DestroiFila(&Q);
  
  return(rot);
}

Imagem *ColoreComponentes(Imagem *img)
{
  Imagem *col=CriaImagem(img->nx,img->ny,3);
  typedef struct _tabela_cor {
    int *vermelho, *verde, *azul;
    int  ncores;
  } TabelaCor;  
  TabelaCor tcor;
  srand(time(NULL));
 
  tcor.ncores   = 65535;
  tcor.vermelho = (int *)calloc(tcor.ncores,sizeof(int));
  tcor.verde    = (int *)calloc(tcor.ncores,sizeof(int));
  tcor.azul     = (int *)calloc(tcor.ncores,sizeof(int));
  
  for (int i=0; i < tcor.ncores; i++){
    tcor.vermelho[i] = NumeroAleatorio(0,255);
    tcor.verde[i]    = NumeroAleatorio(0,255);
    tcor.azul[i]     = NumeroAleatorio(0,255);
  }
  
  for (int y=0; y < img->ny; y++)
    for (int x=0; x < img->nx; x++){
      if (img->banda[0][y][x]!=0){ /* foreground */
	col->banda[0][y][x] = tcor.vermelho[img->banda[0][y][x]];
	col->banda[1][y][x] = tcor.verde[img->banda[0][y][x]];
	col->banda[2][y][x] = tcor.azul[img->banda[0][y][x]];
      }
    }

  free(tcor.vermelho);
  free(tcor.verde);
  free(tcor.azul);
  
  return(col);
}



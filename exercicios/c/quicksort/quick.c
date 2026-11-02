#include<stdio.h>
#include<stdlib.h>

typedef struct Celula{
  struct Celula *prox;
  struct Celula *ant;
  int elemento;
}Celula;


typedef struct Lista{
  Celula *inicio;
  Celula *fim;

}Lista;

Celula* iniciarCelula(int num){
  Celula *nova = (Celula *) malloc(sizeof(Celula));
  nova->prox = NULL;
  nova->ant = NULL;
  nova->elemento = num;
  return nova;
}

Lista* iniciarLista(){
  Lista *l = (Lista *) malloc(sizeof(Lista));
  Celula *inicio = (Celula *) malloc(sizeof(Celula));
  l->inicio = inicio;
  l->fim = inicio;
  return l;
}

void adicionarFim(Lista *l, int num){
  Celula *nova = iniciarCelula(num);
  l->fim->prox = nova;
  nova->ant  = l->fim;
  l->fim = nova;
}

void troca(Celula *i, Celula *j){
  int tmp = i->elemento;
  i->elemento = j->elemento;
  j->elemento = tmp;

}

Celula* particiona(Celula *inicio, Celula *fim){
  Celula *i = inicio;
  Celula *j = fim;
  int p = inicio->elemento;

  while(i!=j){
    while(i!=NULL && i->elemento < p){
      i = i->prox;
    }
    while(j!=NULL && j->elemento > p){
      j = j->ant;
    }

    if(i == j || j->prox == i){
      return j;
    }

    troca(i,j);
    i = i->prox;
    j = j->ant;

  }
}

void quicksort( Celula *inicio, Celula *fim){
  if(inicio != NULL && fim != NULL && inicio != fim){
    Celula *p = particiona(inicio, fim);

    quicksort(inicio, p);
    quicksort(p->prox, fim);
  }
}

int main(){
  Lista *l = iniciarLista();
  
  for(int i =0; i<10; i++){
    int num;
    scanf("%d",&num);
    adicionarFim(l,num);
  }
  quicksort(l->inicio->prox,l->fim);

  for(Celula *i = l->inicio->prox; i != NULL; i = i->prox){
    printf("%d ",i->elemento);
  }

  return 0;
}

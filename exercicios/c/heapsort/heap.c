#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Filme{
  int premios;
  int ano;
  char titulo[101];
}Filme;

int compara(Filme a, Filme b) {
    if (a.premios != b.premios) {
        return a.premios - b.premios;    
    }
    if (a.ano != b.ano) {
        return b.ano - a.ano;             
    }
    return -strcmp(a.titulo, b.titulo);    
}



void heapify(Filme arr[], int n, int i){
  int maior = i;
  int esq = 2*i+1;
  int dir = 2*i+2;
  
  if(esq<n && compara(arr[esq],arr[maior]) > 0) maior = esq;
  if(dir<n && compara(arr[dir],arr[maior]) > 0) maior = dir;

  if(i!=maior){
    Filme tmp = arr[maior];
    arr[maior] = arr[i];
    arr[i] = tmp;
    heapify(arr,n,maior);
  }
}

void heapsort(Filme arr[],int n, int k){
  if(k>n) k=n;
  for(int i = n/2-1; i >= 0; i--){
    heapify(arr,n,i);
  }

  for(int i = n-1; i >= n-k; i--){
    Filme tmp = arr[0];
    arr[0] = arr[i];
    arr[i] = tmp;
    heapify(arr,i,0);
  }
}

int main(){

  int n, k;

  while(scanf("%d%d",&n,&k) == 2){
    Filme *f = (Filme *)malloc(sizeof(Filme)*n);
    for(int i = 0; i < n;i++){
      scanf("%d %d %100[^\r\n]", &f[i].premios, &f[i].ano, f[i].titulo);
    }
    heapsort(f,n,k);
    for (int i = n - 1; i >= n - k; i--) {
      printf("%d %d %s\n", f[i].premios, f[i].ano, f[i].titulo);
    }
  }

  return 0;
}

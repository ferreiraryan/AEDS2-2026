#include <stdio.h>
#include <stdlib.h>
typedef struct {
	char nome[32];
	int hora;
	int minutos;
	int segundos;
	int total_tempo;
} Corredores;


int main(){
	int n,k;
	while(scanf("%d%d",&n,&k) == 2){
    Corredores c[n];
    for (int i = 0; i < n; i++) {
      scanf("%31s %d %d %d", c[i].nome, &c[i].hora, &c[i].minutos, &c[i].segundos);
      c[i].total_tempo = (c[i].hora * 3600) + (c[i].minutos * 60) + c[i].segundos;
    }


    int menor = 0;
    for(int i =0; i<k;i++){
      menor = i;
      for(int j = i; j < n; j++){
        if(c[j].total_tempo < c[menor].total_tempo ){
          menor = j;
        }
      }
      if (menor != i) {
        Corredores tmp = c[i];
        c[i] = c[menor];
        c[menor] = tmp;
      }

    }
      
    for(int i =0; i<k;i++){
      printf("%s %d %d %d\n",c[i].nome,c[i].hora,c[i].minutos,c[i].segundos);
    }
  }
  return 0;
}

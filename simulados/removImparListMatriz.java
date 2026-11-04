


void percorreMatriz(Matriz matriz){
  CelulaMat linha = matriz.inicio;

  while(linha != null){
    CelulaMat atual = linha;
    while(atual!=null){
      if(atual.primeiro.prox != null){
        removeImp(atual);
      }
      
      atual = atual.prox;
    }
    linha = linha.inf;
  }
}

void removeImp(CelulaMat cel){
  Celula ant = cel.inicio;
  Celula p = inicio.prox;

  while(p != null){
    if(p.numero % 2 != 0 ){
      ant.prox = p.prox;
      if(p == cel.ultimo){
        cel.ultimo = ant;
      }
      p = p.prox;
    }
    else{
      ant = p;
      p = p.prox;
    }
  }

}

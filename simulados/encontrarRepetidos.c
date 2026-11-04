


Celula* encontrarRepetidos(No* raiz, CelulaMatriz* inicio){
  Celula *cabeca = (Celula *) malloc(sizeof(Celula));
  cabeca->prox = NULL;

  CelulaMatriz* linha = inicio;
  while(linha != NULL){
    CelulaMatriz* atual = linha;
    while(atual != NULL){
      if(buscarArvore(raiz,i->numeor)){
        Celula *nova = (Celula *) malloc(sizeof(Celula));
        nova->numero = i->elemento;

        Celula* tmp = cabeca;
        while(tmp->prox != null && tmp->prox->num > nova->numero){
          tmp = tmp->prox
        }
        nova->prox = tmp->prox;
        tmp->prox = nova;
      }
      atual-> atual->prox;
    }
    linha = linha->inf;
  }
  return cabeca;
}

int buscarArvore(No* raiz, int elemento){
  if(raiz == NULL) return 0;
  if(elemento == raiz.elemento){
    return 1;
  } else if(elemento < raiz->elemento){
    return buscarArvore(raiz.esq,elemento);
  } else{
    return buscarArvore(raiz.dir, elemento);
  }


}

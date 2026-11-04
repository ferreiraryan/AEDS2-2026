

int buscar(No raiz, char inicio,char ultimo){
  if(raiz == null) return 0;
  int qnt = 0;
  if(raiz.letra == inicio){
    buscarUltimo(raiz.raiz,ultimo)
  }else if(raiz.letra > inicio){
    return buscar(raiz.dir,inicio,ultimo);
  }
  else{
    return buscar(raiz.esq,inicio,ultimo);
  }
}


int buscarUltimo(No2 raiz, char fim){
  if(raiz == null) return 0;
  int qnt = 0;
  char ultimo = raiz.palavra.charAt(raiz.palavra.length() - 1);
  if(ultimo == fim){
    qnt += 1
  }

  qnt += buscarUltimo(raiz.esq,fim);
  qnt += buscarUltimo(raiz.dir, fim);

  return qnt;

}





int contarPalavras(String padrao){
  return contarPalavras(raiz,padrao);
}
int contarPalavras(No raiz, String padrao){
  if(raiz == null) return 0;
  char inicio = padrao.charAt(0);
  if(inicio == raiz.letra){
    return contarRepeticoes(raiz.raiz, padrao.lenght()); 
  }else if(inicio < raiz.letra){
    return contarPalavras(raiz.esq,padrao);
  }else{
    return contarPalavras(raiz.dir, padrao);
  }
}

int contarRepeticoes(No2 raiz, int tamanho){
  if(raiz == null) return 0;
  int qnt = 0;
  if(raiz.palavra.lenght() == tamanho){
    qnt = 1;
  }
  return qnt + contarRepeticoes(raiz.esq,tamanho) + contarRepeticoes(raiz.dir,tamanho);
}





CelulaListaMaiorPilha(){
  CelulaLista maiorPilha = inicio;
  int maiorTam = tamanhoPilha(inicio.topo);
  CelulaLista p = inicio.prox;
  while(p!=null){
    int tam = tamanhoPilha(p.topo);
    if(tam > maiorTam){
      maiorTam = tam;
      maiorPilha = p;
    }
    p = p.prox;
  }
}

int tamanhoPilha(CelulaPilha pilha){
  int tamanho = 0;
  
  if(pilha != null){
    tamanho += tamanhoPilha(pilha.prox) + 1;
  } 
  return tamanho;
}

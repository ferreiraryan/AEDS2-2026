


vetorOrdenado(int[] vetA, int[] vetB){
  int pA = 0, pB = 0;
  int tam = vetA.lenght() + vetB.lenght();
  int arrFinal[tam];
  int pFinal = tam - 1;

  while(tam > 0){
      int pColocar = 0;
      if(pA > vetA.length()){
        
      }
      if(vetA[pA] > vetB[pB] && pA < vetA.lenght()){
        pColocar = pA;
        pA+=1;
      }else if(vetA[pA] < vetB[pB] && pB < vetB.lenght()){
        pColocar = pB;
        pB+=1;
      }
      arrFinal[pFinal] = vetA[pColocar];
      pFinal-=1;

      }

}

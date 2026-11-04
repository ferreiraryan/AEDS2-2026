


int particiona(int[] arr, int inicio,int fim){
  int i = inicio -1;
  int j = fim + 1;

  int pivo = arr[inicio+(fim-inicio)/2];

  while(i<j){
    do{
      i++;
    }while(arr[i] < pivo);

    do{
      j--;
    }while(arr[j] > pivo);

    if(i>=j){
      return j;
    }

    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

void quicksort(int[] arr, int inicio, int fim,int k){

  if(inicio >= fim) return;
  
  int p = particiona(arr,inicio,fim);

  quicksort(arr,inicio,p);

  if(p + 1 < k ){
    quicksort(arr,p+1,fim);
  }
}

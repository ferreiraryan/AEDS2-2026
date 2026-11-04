

void heapify(int[] arr, int n,int i){
  int maior = i; 
  int esq = 2*i+1;
  int dir = 2*i+2;

  if(esq<n && arr[esq] > arr[dir]) maior = esq;
  if(dir<n && arr[dir] > arr[dir]) maior = dir;
 
  if(maior != i){
    int tmp = arr[maior];
    arr[maior] = arr[i];
    arr[i] = tmp;
    heapify(arr,n,maior);
  }
}

void heapsort(){
  

}

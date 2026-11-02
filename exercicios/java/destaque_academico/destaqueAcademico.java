import java.util.*;

class Aluno{
  int nota_final;
  int num_faltas;
  String nome;

  Aluno(int nota_final, int num_faltas, String nome){
    this.nome = nome;
    this.num_faltas = num_faltas;
    this.nota_final = nota_final;
  }

  String format(){
    return nota_final + " " + num_faltas + " " + nome;
  }

}

public class destaqueAcademico{

  static void quicksort(Aluno[] a, int esq, int dir,int k){
    if(esq < dir){
      int pivo = particiona(a,esq,dir);

      quicksort(a,esq,pivo,k);

      if(pivo < k-1){ 
      quicksort(a,pivo+1, dir,k);
      }
    }
  }

  static int compara(Aluno a, Aluno b){
    if(a.nota_final > b.nota_final) return -1;
    else if(a.nota_final < b.nota_final) return 1;
    else{
      if(a.num_faltas < b.num_faltas) return -1;
      else if(a.num_faltas > b.num_faltas) return 1;
      else{
        return a.nome.compareTo(b.nome);
      }
    }
  }

  

  static int particiona(Aluno[] a, int esq,int dir){
    Aluno pivo = a[esq + (dir-esq)/2];
    int i = esq;
    int j = dir;
    while (i <= j){
      while(compara(a[i],pivo) < 0){
        i++;
      }
      while(compara(a[j],pivo) > 0){
        j--;
      }

      if(i <=j){
        swap(a,i,j);
        i++;
        j--;
      } 
    }
    if(j > esq) return j;
    return esq;
  }




  static void swap(Aluno[] a, int i, int j){
    Aluno tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }

  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);

    while(sc.hasNextInt()){
      int n,k;
      n = sc.nextInt();
      k = sc.nextInt();
      Aluno[] alunos = new Aluno[n];
      sc.nextLine();
      for(int i = 0; i <n; i++){
        String buff = sc.nextLine();
        String[] buffers = buff.split(" ",3);
        int num = Integer.parseInt(buffers[1]);
        int nota = Integer.parseInt(buffers[0]);
        String nome = buffers[2];
        alunos[i] = new Aluno(nota,num,nome);
      }

      quicksort(alunos,0,n-1,k);

      for(int i = 0; i <k; i++){
        System.out.println(alunos[i].format());
      }
    
      
    }
  }


}

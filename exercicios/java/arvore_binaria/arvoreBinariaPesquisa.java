import java.util.Scanner;
class No{
  No esq;
  No dir;
  int valor;

  No(int valor){
    esq = null;
    dir = null;
    this.valor = valor;
  }


}
class arvoreBinaria{
  No raiz;

  arvoreBinaria(){
    raiz = null;
  }

  void inserir(int valor){
    raiz = inserirRecursivo(raiz,valor);
  }

  boolean pesquisar(int valor){
    boolean resp = pesquisarRecursivo(this.raiz, valor);
    if (resp) {
        System.out.println("S");
      } else {
        System.out.println("N");
      }
      return resp;
  }

  boolean pesquisarRecursivo(No atual, int valor){
    if(atual == null){ 
      return false;
    }
    System.out.print(atual.valor + " ");
    if(atual.valor == valor){
      return true;
    }
    else if(valor < atual.valor){
      return pesquisarRecursivo(atual.esq,valor);
    }else {
      return pesquisarRecursivo(atual.dir, valor);
    }

  }

  No inserirRecursivo(No atual, int x){
    if(atual == null){
      return new No(x);
    } else if(x < atual.valor){
      atual.esq = inserirRecursivo(atual.esq, x);
    } else if(x > atual.valor){
      atual.dir = inserirRecursivo(atual.dir,x);
    }
    return atual;
  }

  public void caminharPre() {
        if (raiz == null) {
            System.out.println("V");
            return;
        }
        caminharPre(raiz);
        System.out.println();
    }

  private void caminharPre(No i) {
    if (i != null) {
      System.out.print(i.valor + " ");
      caminharPre(i.esq);
      caminharPre(i.dir);
    }
  }

  public void caminharPos() {
    if (raiz == null) {
      System.out.println("V");
        return;
      }
      caminharPos(raiz);
      System.out.println();
  }

  private void caminharPos(No i) {
    if (i != null) {
      caminharPos(i.esq);
      caminharPos(i.dir);
      System.out.print(i.valor + " ");
    }
  }

  public void caminharEm() {
    if (raiz == null) {
      System.out.println("V");
      return;
    }
    caminharEm(raiz);
    System.out.println();
  }

  private void caminharEm(No i) {
    if (i != null) {
      caminharEm(i.esq);
      System.out.print(i.valor + " ");
      caminharEm(i.dir);
    }
  }
}



public class arvoreBinariaPesquisa{

  public static void main(String[] args){

    Scanner sc = new Scanner(System.in);
    arvoreBinaria arvore = new arvoreBinaria();

    while (sc.hasNext()) {
        String comando = sc.next();

        if (comando.equals("I")) {
            int x = sc.nextInt();
            arvore.inserir(x);
        } else if (comando.equals("P")) {
            int y = sc.nextInt();
            arvore.pesquisar(y);
        } else if (comando.equals("PRE")) {
            arvore.caminharPre();
        } else if (comando.equals("POS")) {
            arvore.caminharPos();
        } else if (comando.equals("EM")) {
            arvore.caminharEm();
        }
    }
    sc.close();
  }
}

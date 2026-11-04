import java.io.BufferedReader;
import java.io.FileReader; import java.io.IOException; import java.util.Locale; import java.util.Scanner;
class Arvore{
  No raiz;
    
  Arvore(){
    this.raiz = null;
  }

  Arvore(Veiculo v){
    this.raiz = new No(v);
  }

  void inserir(Veiculo v){
    this.raiz = inserir(v,raiz);
  }

  No inserir(Veiculo v, No raiz){
    if(raiz == null){
       return new No(v);
    }
    if(Maior(v,raiz.v)){
      raiz.dir = inserir(v,raiz.dir);
    }else if(Maior(raiz.v,v)){
      raiz.esq = inserir(v,raiz.esq);
    }
    
    return raiz;
  }

  void pesquisar(String chave){
    System.out.print("raiz ");
    if(pesquisar(this.raiz, chave)){
      System.out.println("SIM");
    }else{
      System.out.println("NAO");
    }
  }

  boolean pesquisar(No raiz,String chave){
    if(raiz == null){
      return false;
    }
    if(Maior(chave,raiz.v.modelo)){
      System.out.print("dir ");
      return pesquisar(raiz.dir,chave);
    }
    else if(Maior(raiz.v.modelo, chave)){
      System.out.print("esq ");
      return pesquisar(raiz.esq,chave);
    }else{
      return true;
    }
  }
  void mostrar(){
    mostrar(raiz);
  }

  void mostrar(No raiz){
    if(raiz == null) return;
    mostrar(raiz.esq);
    System.out.println(raiz.v.format());
    mostrar(raiz.dir);
  }


 private static boolean Maior(String a, String b) {
    return a.compareTo(b) > 0;
  }
  private static boolean Maior(Veiculo a, Veiculo b) {
    return a.modelo.compareTo(b.modelo) > 0;
  }

}
class No {
  Veiculo v;
  No esq;
  No dir;

  No(Veiculo v){
    this.v = v;
    this.esq = null;
    this.dir = null;
  }

}







class LeitorCsv {
  public static Veiculo[] ler(String caminhoArquivo) {
    Veiculo[] veiculos = new Veiculo[10000];
    int n = 0;
    try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
      String linha = br.readLine();
      while ((linha = br.readLine()) != null) {
        veiculos[n++] = Veiculo.parseVeiculo(linha);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }

    Veiculo[] resultado = new Veiculo[n];
    System.arraycopy(veiculos, 0, resultado, 0, n);
    return resultado;
  }
}

class Data {
  private int ano;
  private int mes;
  private int dia;

  Data(int ano, int mes, int dia) {
    this.ano = ano;
    this.mes = mes;
    this.dia = dia;
  }

  String format() {
    return String.format("%02d/%02d/%04d", dia, mes, ano);
  }

  static Data parseData(String s) {
    String buffData[] = s.split("-");
    int ano = Integer.parseInt(buffData[0]);
    int mes = Integer.parseInt(buffData[1]);
    int dia = Integer.parseInt(buffData[2]);
    return new Data(ano, mes, dia);
  }
}

class Veiculo {
  int id;
  String marca;
  String modelo;
  int ano;
  String categoria;
  String combustivel[];
  int cilindros;
  double cilindrada;
  String transmissao;
  String tracao;
  double consumoCidade;
  double consumoEstrada;
  double co2;
  boolean turbo;
  Data dataRegistro;

  Veiculo(int id, String marca, String modelo, int ano, String categoria, String combustivel[], int cilindros,
      double cilindrada, String transmissao, String tracao, double consumoCidade, double consumoEstrada, double co2,
      boolean turbo, Data dataRegistro) {
    this.id = id;
    this.marca = marca;
    this.modelo = modelo;
    this.ano = ano;
    this.categoria = categoria;
    this.combustivel = combustivel;
    this.cilindros = cilindros;
    this.cilindrada = cilindrada;
    this.transmissao = transmissao;
    this.tracao = tracao;
    this.consumoCidade = consumoCidade;
    this.consumoEstrada = consumoEstrada;
    this.co2 = co2;
    this.turbo = turbo;
    this.dataRegistro = dataRegistro;
  }

  String format() {
    String combustivelStr = "[";
    for (int i = 0; i < combustivel.length; i++) {
      combustivelStr += combustivel[i];
      if (i + 1 != combustivel.length)
        combustivelStr += ",";
    }
    combustivelStr += "]";

    String cCidade = String.format(Locale.US, "%.2f", consumoCidade);
    String cEstrada = String.format(Locale.US, "%.2f", consumoEstrada);

    return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano + " ## " + categoria + " ## " + combustivelStr
        + " ## " + cilindros + " ## " + cilindrada + " ## " + transmissao + " ## " + tracao + " ## " + cCidade
        + " ## " + cEstrada + " ## " + co2 + " ## " + turbo + " ## " + dataRegistro.format() + "]";
  }
  // id,marca,modelo,ano,categoria,combustivel,cilindros,cilindrada,transmissao,tracao,consumo_cidade,consumo_estrada,co2,turbo,data_registro

  static Veiculo parseVeiculo(String s) {
    String buff[] = s.split(",");
    int id = Integer.parseInt(buff[0]);
    String marca = buff[1];
    String modelo = buff[2];
    int ano = Integer.parseInt(buff[3]);
    String categoria = buff[4];
    String combustivel[] = buff[5].split(";");
    int cilindros = Integer.parseInt(buff[6]);
    double cilindrada = Double.parseDouble(buff[7]);
    String transmissao = buff[8];
    String tracao = buff[9];
    double consumoCidade = Double.parseDouble(buff[10]);
    double consumoEstrada = Double.parseDouble(buff[11]);
    double co2 = Double.parseDouble(buff[12]);
    boolean turbo = Boolean.parseBoolean(buff[13]);
    Data dataRegistro = Data.parseData(buff[14]);
    return new Veiculo(id, marca, modelo, ano, categoria, combustivel, cilindros, cilindrada, transmissao, tracao,
        consumoCidade, consumoEstrada, co2, turbo, dataRegistro);
  }
}

public class arvoreBinaria{

    public static void main(String[] args) {
    Veiculo[] veiculos = LeitorCsv.ler("/tmp/veiculos.csv");
    Arvore selecionados = new Arvore();
    int id, totalSelecionados = 0;

    Scanner sc = new Scanner(System.in);
    String input;
    while (sc.hasNext()) {
      input = sc.next();
      if (input.equals("-1"))
        break;

      id = Integer.parseInt(input);
      for (Veiculo v : veiculos) {
        if (v.id == id) {
          selecionados.inserir(v);
        }
      }
    }
    sc.nextLine();
    input = sc.nextLine();
    while(!input.equals("FIM")){
      selecionados.pesquisar(input);
      input = sc.nextLine();
    }
    selecionados.mostrar();
  }

}

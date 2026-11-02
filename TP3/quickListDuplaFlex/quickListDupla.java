import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Locale;
import java.util.Scanner;

class Lista {
  Celula inicio;
  Celula fim;
  int tamanho = 0;

  Lista() {
    this.inicio = new Celula();
    this.fim = this.inicio;
  }

  void inserirFim(Veiculo v) {
    Celula nova = new Celula(v);
    nova.ant = this.fim;
    this.fim.prox = nova;
    this.fim = nova;
    tamanho++;
  }
}

class Celula {
  Veiculo elemento;
  Celula prox;
  Celula ant;

  Celula() {
    elemento = null;
    prox = null;
    ant = null;
  }

  Celula(Veiculo v) {
    this.elemento = v;
    prox = null;
    ant = null;

  }
}

class LeitorCsv {
  public static Lista ler(String caminhoArquivo) {
    Lista l = new Lista();
    try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
      String linha = br.readLine();
      while ((linha = br.readLine()) != null) {
        l.inserirFim(Veiculo.parseVeiculo(linha));
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
    return l;
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
  private int id;
  private String marca;
  private String modelo;
  private int ano;
  private String categoria;
  private String combustivel[];
  private int cilindros;
  private double cilindrada;
  private String transmissao;
  private String tracao;
  private double consumoCidade;
  private double consumoEstrada;
  private double co2;
  private boolean turbo;
  private Data dataRegistro;

  public String getMarca() {
    return this.marca;
  }

  public double getConsumoCidade() {
    return this.consumoCidade;
  }

  public double getConsumoEstrada() {
    return this.consumoEstrada;
  }

  public String getCategoria() {
    return this.categoria;
  }

  public int getId() {
    return this.id;
  }

  public double getCo2() {
    return this.co2;
  }

  public String getTransmissao() {
    return this.transmissao;
  }

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

public class quickListDupla {
  public static void quicksort(Celula esq, Celula dir, int esqIdx, int dirIdx) {
    Celula i = esq;
    Celula j = dir;
    int iIdx = esqIdx;
    int jIdx = dirIdx;

    int meioPassos = (dirIdx - esqIdx) / 2;
    Celula meio = esq;
    for (int k = 0; k < meioPassos; k++) {
      meio = meio.prox;
    }
    Veiculo pivo = meio.elemento;

    while (iIdx <= jIdx) {
      while (comparar(i.elemento, pivo) < 0) {
        i = i.prox;
        iIdx++;
      }
      while (comparar(j.elemento, pivo) > 0) {
        j = j.ant;
        jIdx--;
      }

      if (iIdx <= jIdx) {
        swap(i, j);
        i = i.prox;
        j = j.ant;
        iIdx++;
        jIdx--;
      }
    }

    if (esqIdx < jIdx) {
      quicksort(esq, j, esqIdx, jIdx);
    }
    if (iIdx < dirIdx) {
      quicksort(i, dir, iIdx, dirIdx);
    }
  }
  public static int comparar(Veiculo a, Veiculo b) {
    if (a.getConsumoEstrada() != b.getConsumoEstrada()) {
      return (a.getConsumoEstrada() > b.getConsumoEstrada()) ? 1 : -1;
    }
    return a.getMarca().compareTo(b.getMarca());
  }

  public static void swap(Celula a, Celula b) {
    Veiculo temp = a.elemento;
    a.elemento = b.elemento;
    b.elemento = temp;
  }

  public static void main(String[] args) {
    Lista veiculos = LeitorCsv.ler("/tmp/veiculos.csv");
    Lista selecionados = new Lista();
    int id;

    Scanner sc = new Scanner(System.in);
    String input;
    while (sc.hasNext()) {
      input = sc.next();
      if (input.equals("-1"))
        break;

      id = Integer.parseInt(input);
      for (Celula i = veiculos.inicio.prox; i != null; i = i.prox) {
        if (i.elemento.getId() == id) {
          selecionados.inserirFim(i.elemento);
        }
      }
    }

    quicksort(selecionados.inicio.prox, selecionados.fim, 0, selecionados.tamanho - 1);

    for (Celula i = selecionados.inicio.prox; i != null; i = i.prox) {
      System.out.println(i.elemento.format());
    }

  }

}

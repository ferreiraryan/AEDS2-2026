import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Locale;
import java.util.Scanner;

class Data {
  private int ano;
  private int mes;
  private int dia;

  public Data() {
  }

  public Data(int ano, int mes, int dia) {
    this.ano = ano;
    this.mes = mes;
    this.dia = dia;
  }

  public int getAno() {
    return ano;
  }

  public void setAno(int ano) {
    this.ano = ano;
  }

  public int getMes() {
    return mes;
  }

  public void setMes(int mes) {
    this.mes = mes;
  }

  public int getDia() {
    return dia;
  }

  public void setDia(int dia) {
    this.dia = dia;
  }

  public static Data parseData(String s) {
    String[] partes = s.split("-");
    return new Data(
        Integer.parseInt(partes[0]),
        Integer.parseInt(partes[1]),
        Integer.parseInt(partes[2]));
  }

  public String format() {
    return String.format(Locale.US, "%02d/%02d/%04d", dia, mes, ano);
  }
}

class Veiculo {
  private int id;
  private String marca;
  private String modelo;
  private int ano;
  private String categoria;
  private String[] combustivel;
  private int cilindros;
  private double cilindrada;
  private String transmissao;
  private String tracao;
  private double consumoCidade;
  private double consumoEstrada;
  private double co2;
  private boolean turbo;
  private Data dataRegistro;

  public Veiculo() {
  }

  public int getId() {
    return id;
  }

  public void setId(int id) {
    this.id = id;
  }

  public String getMarca() {
    return marca;
  }

  public void setMarca(String marca) {
    this.marca = marca;
  }

  public String getModelo() {
    return modelo;
  }

  public void setModelo(String modelo) {
    this.modelo = modelo;
  }

  public int getAno() {
    return ano;
  }

  public void setAno(int ano) {
    this.ano = ano;
  }

  public String getCategoria() {
    return categoria;
  }

  public void setCategoria(String categoria) {
    this.categoria = categoria;
  }

  public String[] getCombustivel() {
    return combustivel;
  }

  public void setCombustivel(String[] combustivel) {
    this.combustivel = combustivel;
  }

  public int getCilindros() {
    return cilindros;
  }

  public void setCilindros(int cilindros) {
    this.cilindros = cilindros;
  }

  public double getCilindrada() {
    return cilindrada;
  }

  public void setCilindrada(double cilindrada) {
    this.cilindrada = cilindrada;
  }

  public String getTransmissao() {
    return transmissao;
  }

  public void setTransmissao(String transmissao) {
    this.transmissao = transmissao;
  }

  public String getTracao() {
    return tracao;
  }

  public void setTracao(String tracao) {
    this.tracao = tracao;
  }

  public double getConsumoCidade() {
    return consumoCidade;
  }

  public void setConsumoCidade(double consumoCidade) {
    this.consumoCidade = consumoCidade;
  }

  public double getConsumoEstrada() {
    return consumoEstrada;
  }

  public void setConsumoEstrada(double consumoEstrada) {
    this.consumoEstrada = consumoEstrada;
  }

  public double getCo2() {
    return co2;
  }

  public void setCo2(double co2) {
    this.co2 = co2;
  }

  public boolean isTurbo() {
    return turbo;
  }

  public void setTurbo(boolean turbo) {
    this.turbo = turbo;
  }

  public Data getDataRegistro() {
    return dataRegistro;
  }

  public void setDataRegistro(Data dataRegistro) {
    this.dataRegistro = dataRegistro;
  }

  public static Veiculo parseVeiculo(String s) {
    Veiculo v = new Veiculo();
    String[] campos = s.split(",", -1);

    v.setId(Integer.parseInt(campos[0]));
    v.setMarca(campos[1]);
    v.setModelo(campos[2]);
    v.setAno(Integer.parseInt(campos[3]));
    v.setCategoria(campos[4]);

    String[] combustiveis = campos[5].split(";");
    for (int i = 0; i < combustiveis.length; i++) {
      combustiveis[i] = combustiveis[i].trim();
    }
    v.setCombustivel(combustiveis);

    v.setCilindros(campos[6].isEmpty() ? 0 : Integer.parseInt(campos[6]));
    v.setCilindrada(campos[7].isEmpty() ? 0.0 : Double.parseDouble(campos[7]));
    v.setTransmissao(campos[8]);
    v.setTracao(campos[9]);
    v.setConsumoCidade(campos[10].isEmpty() ? 0.0 : Double.parseDouble(campos[10]));
    v.setConsumoEstrada(campos[11].isEmpty() ? 0.0 : Double.parseDouble(campos[11]));
    v.setCo2(campos[12].isEmpty() ? 0.0 : Double.parseDouble(campos[12]));
    v.setTurbo(campos[13].contains("true"));
    v.setDataRegistro(Data.parseData(campos[14]));

    return v;
  }

  public String format() {
    String strCombustiveis = String.join(", ", combustivel);

    return String.format(Locale.US,
        "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %b ## %s]",
        id, marca, modelo, ano, categoria, strCombustiveis, cilindros, cilindrada,
        transmissao, tracao, consumoCidade, consumoEstrada, co2,
        turbo, dataRegistro.format());
  }
}

class LeitorCsv {
  public static Veiculo[] ler(String caminhoArquivo) {
    Veiculo[] veiculos = new Veiculo[10000];
    int n = 0;
    try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
      String linha = br.readLine(); // Pula o cabeçalho
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

class Lista {
  private Veiculo[] array;
  private int n;

  public Lista(int tamanho) {
    array = new Veiculo[tamanho];
    n = 0;
  }

  public void inserirInicio(Veiculo veiculo) {
    if (n >= array.length)
      return;
    for (int i = n; i > 0; i--) {
      array[i] = array[i - 1];
    }
    array[0] = veiculo;
    n++;
  }

  public void inserir(Veiculo veiculo, int pos) {
    if (n >= array.length || pos < 0 || pos > n)
      return;
    for (int i = n; i > pos; i--) {
      array[i] = array[i - 1];
    }
    array[pos] = veiculo;
    n++;
  }

  public void inserirFim(Veiculo veiculo) {
    if (n >= array.length)
      return;
    array[n] = veiculo;
    n++;
  }

  public Veiculo removerInicio() {
    if (n == 0)
      return null;
    Veiculo resp = array[0];
    n--;
    for (int i = 0; i < n; i++) {
      array[i] = array[i + 1];
    }
    return resp;
  }

  public Veiculo remover(int pos) {
    if (n == 0 || pos < 0 || pos >= n)
      return null;
    Veiculo resp = array[pos];
    n--;
    for (int i = pos; i < n; i++) {
      array[i] = array[i + 1];
    }
    return resp;
  }

  public Veiculo removerFim() {
    if (n == 0)
      return null;
    return array[--n];
  }

  public void mostrar() {
    for (int i = 0; i < n; i++) {
      System.out.println("[" + i + "] " + array[i].format());
    }
  }
}

public class Main {
  public static Veiculo buscar(Veiculo[] veiculos, int id) {
    for (Veiculo v : veiculos) {
      if (v.getId() == id) {
        return v;
      }
    }
    return null;
  }

  public static void main(String[] args) {
    Veiculo[] veiculos = LeitorCsv.ler("/tmp/veiculos.csv");
    Lista lista = new Lista(10000);
    Scanner sc = new Scanner(System.in);

    String input;
    while (sc.hasNext()) {
      input = sc.next();
      if (input.equals("-1"))
        break;

      int idBusca = Integer.parseInt(input);
      Veiculo v = buscar(veiculos, idBusca);
      if (v != null) {
        lista.inserirFim(v);
      }
    }

    int numOperacoes = sc.nextInt();
    for (int i = 0; i < numOperacoes; i++) {
      String comando = sc.next();

      if (comando.equals("II")) {
        int id = sc.nextInt();
        Veiculo v = buscar(veiculos, id);
        if (v != null)
          lista.inserirInicio(v);
      } else if (comando.equals("I")) {
        int pos = sc.nextInt();
        int id = sc.nextInt();
        Veiculo v = buscar(veiculos, id);
        if (v != null)
          lista.inserir(v, pos);
      } else if (comando.equals("IF")) {
        int id = sc.nextInt();
        Veiculo v = buscar(veiculos, id);
        if (v != null)
          lista.inserirFim(v);
      } else if (comando.equals("RI")) {
        Veiculo rem = lista.removerInicio();
        if (rem != null)
          System.out.println("(R) " + rem.getMarca() + " " + rem.getModelo());
      } else if (comando.equals("R")) {
        int pos = sc.nextInt();
        Veiculo rem = lista.remover(pos);
        if (rem != null)
          System.out.println("(R) " + rem.getMarca() + " " + rem.getModelo());
      } else if (comando.equals("RF")) {
        Veiculo rem = lista.removerFim();
        if (rem != null)
          System.out.println("(R) " + rem.getMarca() + " " + rem.getModelo());
      }
    }

    lista.mostrar();
    sc.close();
  }
}

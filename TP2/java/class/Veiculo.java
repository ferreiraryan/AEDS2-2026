public class Veiculo {
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

  public String gettransmissao() {
    return transmissao;
  }

  public void settransmissao(String transmissao) {
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

  public String format() {
    return id + "##" + marca + "##" + modelo + "##" + ano + "##" + categoria + "##" + combustivel + "##" + cilindros
        + "##" + cilindrada + "##" + transmissao + "##" + tracao + "##" + consumoCidade + "##" + consumoEstrada + "##"
        + co2 + "##" + turbo + "##" + dataRegistro;
  }

}

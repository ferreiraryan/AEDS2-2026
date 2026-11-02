import java.util.Scanner;

public class Is {
  // Verifica se todos os caracteres da string sao vogais e retorna true caso sim
  public static boolean verificaVogais(String texto) {
    for (int i = 0; i < texto.length(); i++) {
      char c = texto.charAt(i);
      if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' &&
          c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
        return false;
      }
    }
    return true;
  }

  // Percorre todos os caracteres e verifica se a string eh composta apenas por
  // consoantes
  public static boolean verificaConsoantes(String texto) {
    for (int i = 0; i < texto.length(); i++) {
      char c = texto.charAt(i);
      boolean isLetra = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
      if (!isLetra) {
        return false;
      }
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
          c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return false;
      }
    }
    return true;
  }

  // Percorre todos os caracteres da String e verifica se esta dentro do intervalo
  // de inteirso da tabela asccii
  public static boolean verificaInteiro(String texto) {
    for (int i = 0; i < texto.length(); i++) {
      if ((int) texto.charAt(i) < 48 || (int) texto.charAt(i) > 57) {
        return false;
      }
    }
    return true;
  }

  // Percorre todos os caracteres da String e verifica se esta dentro do intervalo
  // de inteiros da tabela asccii, depois verifica se eh numero fracionado
  public static boolean verificaReal(String texto) {
    int apareceVirgula = 0;
    for (int i = 0; i < texto.length(); i++) {
      char c = texto.charAt(i);

      if (c == '.' || c == ',') {
        apareceVirgula++;
      } else if (((int) c < 48 || (int) c > 57)) {
        return false;
      }
    }
    if (apareceVirgula <= 1)
      return true;
    return false;
  }

  public static boolean ehFim(String str) {
    return str.length() == 3 &&
        str.charAt(0) == 'F' &&
        str.charAt(1) == 'I' &&
        str.charAt(2) == 'M';
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    while (scanner.hasNextLine()) {
      String texto = scanner.nextLine();

      if (ehFim(texto)) {
        break;
      }

      System.out.print(verificaVogais(texto) ? "SIM " : "NAO ");
      System.out.print(verificaConsoantes(texto) ? "SIM " : "NAO ");
      System.out.print(verificaInteiro(texto) ? "SIM " : "NAO ");
      System.out.print(verificaReal(texto) ? "SIM\n" : "NAO\n");

    }
    scanner.close();
  }
}

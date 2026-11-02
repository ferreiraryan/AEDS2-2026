import java.util.Random;
import java.util.Scanner;

public class AltercaoAleatoria {
  // Define o gerador como unico e imutavel para toda a classe
  private static final Random gerador = new Random();

  // Verifica se chegou ao FIM do pub.in
  public static boolean ehFim(String str) {
    return str.length() == 3 &&
        str.charAt(0) == 'F' &&
        str.charAt(1) == 'I' &&
        str.charAt(2) == 'M';
  }

  public static String Altrador(String texto) {

    String newText = new String();
    char cTrocado = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
    char c = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));

    // Itera sobre a String verificando cada caractere,
    // caso o caractere deva ser mudado, adicona o outro caracatere a nova String
    // caso nao, adiciona o mesmo caractere a nova string
    for (int i = 0; i < texto.length(); i++) {
      if (texto.charAt(i) == cTrocado) {
        newText += c;
      } else {
        newText += texto.charAt(i);
      }
    }
    return newText;

  }

  public static void main(String[] args) {
    gerador.setSeed(4);
    Scanner scanner = new Scanner(System.in);
    while (scanner.hasNextLine()) {
      String text = scanner.nextLine();
      if (ehFim(text)) {
        break;
      }
      // Chama o metodo alterador e exibe o resultado
      System.out.println(Altrador(text));
    }
    scanner.close();
  }
}

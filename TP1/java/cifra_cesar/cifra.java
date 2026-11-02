import java.util.Scanner;

public class cifra {
  public static String cifrador(String Texto) {
    String TextoCifrado = new String();
    // Percorre a String caractere por caractere
    for (int i = 0; i < Texto.length(); i++) {
      char c = Texto.charAt(i);
      // Troca o caractere atual pelo proprio caractere mais 3
      // movendo assim para a proxima letra
      char charcifrado = (char) (c + 3);
      TextoCifrado += charcifrado;
    }
    return TextoCifrado;

  }

  // Verifica se chegou ao FIM do pub.in
  public static boolean ehFim(String str) {
    return str.length() == 3 &&
        str.charAt(0) == 'F' &&
        str.charAt(1) == 'I' &&
        str.charAt(2) == 'M';
  }

  public static void main(String[] args) {

    Scanner scanner = new Scanner(System.in);
    while (scanner.hasNextLine()) {
      String Text = scanner.nextLine();
      if (Text.length() == 0) {
        continue;
      }
      if (ehFim(Text)) {
        break;
      }

      System.out.println(cifrador(Text));
    }
    scanner.close();

  }
}

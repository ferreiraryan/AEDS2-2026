import java.util.Scanner;

public class inversaoStringRecursivo {
  // Verifica se chegou ao FIM do pub.in
  public static boolean ehFim(String str) {
    return str.length() == 3 &&
        str.charAt(0) == 'F' &&
        str.charAt(1) == 'I' &&
        str.charAt(2) == 'M';
  }

  // troca o caractere i pelo recursivo i-1, trocando o primeiro pelo ultimo
  public static void inverter(String str, int i) {
    int inicio = 0;
    while (inicio <= i && (str.charAt(inicio) == ' ' || str.charAt(inicio) == '\t' || str.charAt(inicio) == '\r')) {
      inicio++;
    }

    if (i < inicio) {
      return;
    }

    System.out.print(str.charAt(i));
    inverter(str, i - 1);
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    while (scanner.hasNextLine()) {
      String str = scanner.nextLine();
      if (ehFim(str)) {
        break;
      }

      inverter(str, str.length() - 1);
      System.out.println();
    }

    scanner.close();
  }

}

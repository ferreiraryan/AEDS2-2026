import java.util.Scanner;

public class validacaoSenha {
  // Metodo necessario pois o pub.in tem um fim antesd do EOF
  public static boolean isFim(String s) {
    return s.length() == 3 &&
        s.charAt(0) == 'F' &&
        s.charAt(1) == 'I' &&
        s.charAt(2) == 'M';
  }

  // Verifica carater a caracter para ver se atende os requisitos da senha
  public static boolean validaSenha(String str) {
    if (str.length() < 8) {
      return false;
    }
    boolean letraMaiuscula = false, letraMinuscula = false, numero = false, caracteresEspecial = false;
    for (int i = 0; i < str.length(); i++) {
      char c = str.charAt(i);
      if (c >= 'A' && c <= 'Z') {
        letraMaiuscula = true;
      } else if (c >= 'a' && c <= 'z') {
        letraMinuscula = true;
      } else if (c >= '0' && c <= '9') {
        numero = true;
      } else if ((c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) {
        caracteresEspecial = true;
      }
    }
    return letraMinuscula && letraMaiuscula && numero && caracteresEspecial;

  }

  public static void main(String[] args) {

    Scanner scanner = new Scanner(System.in);
    while (scanner.hasNextLine()) {
      String Text = scanner.nextLine();

      if (Text.length() == 0 || isFim(Text)) {
        break;
      }

      if (validaSenha(Text)) {
        System.out.println("SIM");
      } else {
        System.out.println("NAO");
      }
    }
    scanner.close();

  }
}

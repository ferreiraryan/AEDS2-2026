import java.util.Scanner;

public class somaDigitosRecursivo {
  // usa a recursividade para somar o proximo digito de um numero ate obter o
  // total
  public static int somaDigitos(int numero) {
    if (numero == 0) {
      return 0;
    }

    int digito = numero % 10;

    return digito + (somaDigitos(numero / 10));
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    while (sc.hasNextInt()) {
      int valor = sc.nextInt();
      System.out.println(somaDigitos(valor));
    }

    sc.close();
  }
}

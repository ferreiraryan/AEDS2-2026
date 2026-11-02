#include <stdio.h>

// Soma os digitos usando a divisao para separar-los
int somaDigitos(int numero) {
  int soma = 0;
  while (numero > 0) {
    int digito = numero % 10;
    soma += digito;
    numero = numero / 10;
  }
  return soma;
}

int main() {
  int num;

  while (scanf("%d", &num) != EOF) {
    printf("%d\n", somaDigitos(num));
  }
  return 0;
}

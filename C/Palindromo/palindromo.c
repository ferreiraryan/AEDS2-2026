#include <stdio.h>

int main() {
  int tamanhoPalavra = 0, EhPalindromo = 1;
  char palavra[50];

  while (palavra[0] != 'F' && palavra[1] != 'I' && palavra[2] != 'M' &&
         tamanhoPalavra != 3) {
    scanf("%s", palavra);
    while (palavra[tamanhoPalavra] != '\0') {
      tamanhoPalavra++;
    }
    for (int i = 0; i < tamanhoPalavra; i++) {
      if (palavra[i] != palavra[(tamanhoPalavra - 1) - i]) {
        EhPalindromo = 0;
        break;
      }
    }

    if (EhPalindromo) {
      printf("SIM\n");
    } else {
      printf("NAO\n");
    }
  }

  return 0;
}

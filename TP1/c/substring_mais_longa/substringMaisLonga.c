#include <stdio.h>

int tamanhoStr(char *str) {
  int i = 0;
  while (str[i] != '\n' && str[i] != '\0') {
    i++;
  }
  return i;
}
// funcao necessaria pois o pub.in termina no fim, nao no EOF
int isFim(const char *s) {
  return (s[0] == 'F' && s[1] == 'I' && s[2] == 'M' &&
          (s[3] == '\0' || s[3] == '\n' || s[3] == '\r'));
}

// itera sobre e string, separa uma substring de tamanho i,
// velirifa se algum caracter se repete, caso se repita, aumenta o tamnho da
// substring ate achar a maior substring
int substringMaisLonga(char str[]) {
  int tamStr = tamanhoStr(str);
  int maior = 0;

  for (int i = 0; i < tamStr; i++) {
    char substringAtual[501];
    int tamAtual = 0;

    for (int j = i; j < tamStr; j++) {
      char c = str[j];
      int repetido = 0;

      for (int k = 0; k < tamAtual; k++) {
        if (substringAtual[k] == c) {
          repetido = 1;
          break;
        }
      }

      if (repetido) {
        break;
      }

      substringAtual[tamAtual] = c;
      tamAtual++;
      substringAtual[tamAtual] = '\0';

      if (tamAtual > maior) {
        maior = tamAtual;
      }
    }
  }

  return maior;
}

int main() {
  char str[500];

  while (scanf("%s", str) == 1) {
    if (isFim(str)) {
      break;
    }
    printf("%d\n", substringMaisLonga(str));
  }
  return 0;
}

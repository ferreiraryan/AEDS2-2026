#include <stdio.h>

// Recebe uma string e clona ela comecado do final, (tamanho- 1 - i),
//  para uma nova. Remove espacos no final
void inverterString(char *string) {
  int inicio = 0;

  while (string[inicio] == ' ' || string[inicio] == '\t') {
    inicio++;
  }

  int tamanho = inicio;

  while (string[tamanho] != '\0' && string[tamanho] != '\n' &&
         string[tamanho] != '\r') {
    tamanho++;
  }

  int tam_real = tamanho - inicio;
  char invertida[tam_real + 1];

  for (int i = 0; i < tam_real; i++) {
    invertida[i] = string[tamanho - 1 - i];
  }
  invertida[tam_real] = '\0';

  printf("%s\n", invertida);
}
// funcao necessaria pois o pub.in termina no fim, nao no EOF
int isFim(const char *s) {
  return (s[0] == 'F' && s[1] == 'I' && s[2] == 'M' &&
          (s[3] == '\0' || s[3] == '\n' || s[3] == '\r'));
}
int main() {
  char string[1000];

  while (fgets(string, sizeof(string), stdin) != NULL) {
    if (isFim(string)) {
      break;
    }
    inverterString(string);

    // printf("%s\n", string);
  }

  return 0;
}

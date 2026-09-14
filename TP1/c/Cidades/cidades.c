#include <stdio.h>

int main() {
  char cidade[100];

  scanf(" %[^\n]", cidade);

  while (!(cidade[0] == 'F' && cidade[1] == 'I' && cidade[2] == 'M')) {

    int tamanho = 0;

    while (cidade[tamanho] != '\0') {
      tamanho++;
    }
    printf("%d\n", tamanho);

    scanf(" %[^\n]", cidade);
  }

  return 0;
}

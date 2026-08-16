#include <stdio.h>

void ParOuImpar(int numero) {

  if (numero % 2 == 0) {
    printf("PAR\n");
    return;
  }
  printf("IMPAR\n");
}

int main() {
  int numero, n;

  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &numero);
    ParOuImpar(numero);
  }

  return 0;
}

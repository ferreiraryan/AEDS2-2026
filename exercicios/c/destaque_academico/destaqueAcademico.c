#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int nota;
  int falta;
  char nome[55];
} Aluno;

int compara(Aluno a, Aluno b) {
  if (a.nota != b.nota)
    return a.nota - b.nota;
  if (a.falta != b.falta)
    return b.falta - a.falta;

  return strcmp(b.nome, a.nome);
}

int particiona(Aluno a[], int inicio, int fim) {
  Aluno pivo = a[(inicio + fim) / 2];
  int i = inicio - 1;
  int j = fim + 1;

  while (i <= j) {
    do {
      i++;
    } while (compara(a[i], pivo) > 0);

    do {
      j--;
    } while (compara(a[j], pivo) < 0);

    if (i >= j) {
      return j;
    }

    Aluno tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }
  return j;
}

void quicksort(Aluno a[], int inicio, int fim, int k) {
  if (inicio >= fim)
    return;

  int p = particiona(a, inicio, fim);

  if (inicio < p) {
    quicksort(a, inicio, p, k);
  }
  if (p + 1 < fim && p + 1 < k) {
    quicksort(a, p + 1, fim, k);
  }
}
int main() {

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    Aluno *a = malloc(n * sizeof(Aluno));
    for (int i = 0; i < n; i++) {
      scanf("%d %d %[^\r\n]", &a[i].nota, &a[i].falta, a[i].nome);
    }
    quicksort(a, 0, n - 1, k);
    for (int i = 0; i < k; i++) {
      printf("%d %d %s\n", a[i].nota, a[i].falta, a[i].nome);
    }
    free(a);
  }
  return 0;
}

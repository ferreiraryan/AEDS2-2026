#include <stdio.h>

int main() {
  char str1[100], str2[100];

  while (scanf("%s %s", str1, str2) != EOF) {
    int i = 0, j = 0;

    while (str1[i] != '\0' && str2[j] != '\0') {
      putchar(str1[i++]);
      putchar(str2[j++]);
    }

    while (str1[i] != '\0') {
      putchar(str1[i++]);
    }

    while (str2[j] != '\0') {
      putchar(str2[j++]);
    }

    putchar('\n');
  }

  return 0;
}

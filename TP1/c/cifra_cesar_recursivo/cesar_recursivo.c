#include <stdio.h>

// funcao necessaria pois o pub.in termina no fim, nao no EOF
int isFim(const char *s) {
  return (s[0] == 'F' && s[1] == 'I' && s[2] == 'M' &&
          (s[3] == '\0' || s[3] == '\n' || s[3] == '\r'));
}

// recebe a string e a posicao incial a ser cifrada,
// apos cifra a posicao e chama a recursividade para a proxima posicao
void cifra(char *str, int i) {
  if (str[i] == '\0' || str[i] == '\n') {
    str[i] = '\0';
    return;
  }
  str[i] = str[i] + 3;
  cifra(str, i + 1);
}

int main() {
  char str[1000];

  while (fgets(str, sizeof(str), stdin) != NULL) {
    if (isFim(str)) {
      break;
    }

    cifra(str, 0);
    printf("%s\n", str);
  }

  return 0;
}

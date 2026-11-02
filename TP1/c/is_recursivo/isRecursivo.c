#include <stdio.h>
#include <stdlib.h>

// verifica o caractere na posicao i e usa a recursividade para verificar o
// proximo ate o final
int somenteVogais(char *str, int i) {
  if (str[i] == '\0' || str[i] == '\n') {
    return 1;
  }

  char c = str[i];

  if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' &&
      c != 'E' && c != 'I' && c != 'O' && c != 'U') {
    return 0;
  }

  return somenteVogais(str, i + 1);
}

// verifica o caractere na posicao i e usa a recursividade para verificar o
// proximo ate o final usando o numero da tabela ascii para validar
int somenteConsoantes(char *str, int i) {
  if (str[i] == '\0' || str[i] == '\n') {
    return 1;
  }

  char c = str[i];

  if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
    return 0;
  }

  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' ||
      c == 'E' || c == 'I' || c == 'O' || c == 'U') {
    return 0;
  }

  return somenteConsoantes(str, i + 1);
}

// verifica o caractere na posicao i e usa a recursividade para verificar o
// proximo ate o final usando a tabela ascci, se chegar no final da
// recursividade quer dizer que eh inteiro
int ehInteiro(char *str, int i) {
  if (str[i] == '\0' || str[i] == '\n') {
    return 1;
  }

  if (i == 0 && (str[i] == '+' || str[i] == '-')) {
    if (str[i + 1] == '\0' || str[i + 1] == '\n') {
      return 0;
    }

    return ehInteiro(str, i + 1);
  }

  if (str[i] < '0' || str[i] > '9') {
    return 0;
  }

  return ehInteiro(str, i + 1);
}

// verifica o caractere na posicao i e usa a recursividade para verificar o
// proximo ate o final usa a tabela ascii para validar se eh um numero, se eh um
// float, caso chegue no final, eh real
int ehReal(char *str, int i, int separador, int digitos) {
  if (str[i] == '\0' || str[i] == '\n') {
    return digitos == 1;
  }

  if (i == 0 && (str[i] == '+' || str[i] == '-')) {
    if (str[i + 1] == '\0' || str[i + 1] == '\n') {
      return 0;
    }

    return ehReal(str, i + 1, separador, digitos);
  }

  if (str[i] == '.' || str[i] == ',') {
    if (separador == 1) {
      return 0;
    }

    return ehReal(str, i + 1, 1, digitos);
  }

  if (str[i] >= '0' && str[i] <= '9') {
    return ehReal(str, i + 1, separador, 1);
  }

  return 0;
}

// Usado para checar se chegou no FIM do pub.in
int isFim(const char *s) {
  return s[0] == 'F' && s[1] == 'I' && s[2] == 'M' &&
         (s[3] == '\0' || s[3] <= 32);
}
int main() {
  char str[1000];

  while (fgets(str, 1000, stdin) != NULL) {
    if (isFim(str)) {
      break;
    }

    printf("%s %s %s %s\n", somenteVogais(str, 0) ? "SIM" : "NAO",
           somenteConsoantes(str, 0) ? "SIM" : "NAO",
           ehInteiro(str, 0) ? "SIM" : "NAO",
           ehReal(str, 0, 0, 0) ? "SIM" : "NAO");
  }

  return 0;
}

#include <stdio.h>

int tamanhoStr(char *str) {
  int i = 0;
  while (str[i] != '\n' && str[i] != '\0') {
    i++;
  }
  return i;
}

// subtrai da tabela ascii os minusculos dos maiusculos
// assim os maiusculos ficam minusculos
char charMinusculo(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

// Utiliza vetor de contagem para cada letra do alfabeto
// se ocorrer na string 1 soma a posicao correspondente da letra
// se ocorrer na string 2 subtrai, assim para ser anagrama o contador inteiro
// tem que ser 0
int verificaAnagrama(char *str1, char *str2) {
  int tamanhostr1 = tamanhoStr(str1), tamanhostr2 = tamanhoStr(str2);

  if (tamanhostr1 != tamanhostr2) {
    return 0;
  }

  int contagem[26];
  for (int i = 0; i < 26; i++) {
    contagem[i] = 0;
  }

  for (int i = 0; i < tamanhostr1; i++) {
    char c1 = charMinusculo(str1[i]);
    char c2 = charMinusculo(str2[i]);
    if (c1 >= 'a' && c1 <= 'z') {
      contagem[c1 - 'a']++;
    }
    if (c2 >= 'a' && c2 <= 'z') {
      contagem[c2 - 'a']--;
    }
  }

  for (int i = 0; i < 26; i++) {
    if (contagem[i] != 0) {

      return 0;
    }
  }
  return 1;
}

int main() {
  char str1[500], str2[500];

  while (scanf("%s %s", str1, str2) == 2) {
    if (verificaAnagrama(str1, str2) == 1) {
      printf("SIM\n");
    } else {
      printf("NAO\n");
    }
  }

  return 0;
}

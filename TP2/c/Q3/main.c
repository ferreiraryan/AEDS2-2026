#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int ano;
  int mes;
  int dia;
} Data;

typedef struct {
  int id;
  char marca[100];
  char modelo[150];
  int ano;
  char categoria[100];
  char combustivel[10][50];
  int cilindros;
  double cilindrada;
  char transmissao[100];
  char tracao[100];
  double consumoCidade;
  double consumoEstrada;
  double co2;
  bool turbo;
  Data dataRegistro;
} Veiculo;

Data parseData(char *s) {
  Data d = {0};
  sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
  return d;
}

void formatData(Data d, char *buffer) {
  sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

char *get_csv_field(char **cursor) {
  if (!*cursor)
    return NULL;
  char *start = *cursor;
  char *end = strchr(start, ',');
  if (end) {
    *end = '\0';
    *cursor = end + 1;
  } else {
    *cursor = NULL;
  }
  return start;
}

Veiculo parseVeiculo(char *s) {
  Veiculo v;
  memset(&v, 0, sizeof(Veiculo));

  char *cursor = s;
  char *field;

  field = get_csv_field(&cursor);
  v.id = field ? atoi(field) : 0;
  field = get_csv_field(&cursor);
  if (field)
    strcpy(v.marca, field);
  field = get_csv_field(&cursor);
  if (field)
    strcpy(v.modelo, field);
  field = get_csv_field(&cursor);
  v.ano = field ? atoi(field) : 0;
  field = get_csv_field(&cursor);
  if (field)
    strcpy(v.categoria, field);

  field = get_csv_field(&cursor);
  if (field) {
    char *comb_token = strtok(field, ";");
    int c_idx = 0;
    while (comb_token && c_idx < 10) {
      if (comb_token[0] == ' ')
        comb_token++;
      strcpy(v.combustivel[c_idx++], comb_token);
      comb_token = strtok(NULL, ";");
    }
  }

  field = get_csv_field(&cursor);
  v.cilindros = (field && *field) ? atoi(field) : 0;
  field = get_csv_field(&cursor);
  v.cilindrada = (field && *field) ? atof(field) : 0.0;
  field = get_csv_field(&cursor);
  if (field)
    strcpy(v.transmissao, field);
  field = get_csv_field(&cursor);
  if (field)
    strcpy(v.tracao, field);
  field = get_csv_field(&cursor);
  v.consumoCidade = (field && *field) ? atof(field) : 0.0;
  field = get_csv_field(&cursor);
  v.consumoEstrada = (field && *field) ? atof(field) : 0.0;
  field = get_csv_field(&cursor);
  v.co2 = (field && *field) ? atof(field) : 0.0;

  field = get_csv_field(&cursor);
  v.turbo = (field && strstr(field, "true") != NULL);

  field = get_csv_field(&cursor);
  if (field)
    v.dataRegistro = parseData(field);

  return v;
}

void formatVeiculo(Veiculo *v, char *buffer, int size) {
  char strCombustiveis[256] = "";

  for (int i = 0; i < 10; i++) {
    if (v->combustivel[i][0] == '\0')
      break;
    if (i > 0)
      strcat(strCombustiveis, ",");
    strcat(strCombustiveis, v->combustivel[i]);
  }

  char dataBuffer[15];
  formatData(v->dataRegistro, dataBuffer);

  snprintf(buffer, size,
           "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## "
           "%.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## "
           "%s ## %s]",
           v->id, v->marca, v->modelo, v->ano, v->categoria, strCombustiveis,
           v->cilindros, v->cilindrada, v->transmissao, v->tracao,
           v->consumoCidade, v->consumoEstrada, v->co2,
           v->turbo ? "true" : "false", dataBuffer);
}

Veiculo *lerCsv(const char *caminhoArquivo, int *n) {
  FILE *f = fopen(caminhoArquivo, "r");
  if (!f)
    return NULL;

  int capacity = 5000;
  Veiculo *arr = malloc(capacity * sizeof(Veiculo));
  char line[1024];

  fgets(line, sizeof(line), f);

  *n = 0;
  while (fgets(line, sizeof(line), f)) {
    line[strcspn(line, "\r\n")] = '\0';

    arr[*n] = parseVeiculo(line);
    (*n)++;

    if (*n >= capacity) {
      capacity *= 2;
      arr = realloc(arr, capacity * sizeof(Veiculo));
    }
  }

  fclose(f);
  return arr;
}

int strcmpIgnoreCase(const char *a, const char *b) {
  while (*a && *b) {
    char ca = (*a >= 'a' && *a <= 'z') ? *a - 32 : *a;
    char cb = (*b >= 'a' && *b <= 'z') ? *b - 32 : *b;
    if (ca != cb)
      return ca - cb;
    a++;
    b++;
  }
  char ca = (*a >= 'a' && *a <= 'z') ? *a - 32 : *a;
  char cb = (*b >= 'a' && *b <= 'z') ? *b - 32 : *b;
  return ca - cb;
}

int main() {
  int n = 0;
  Veiculo *veiculos = lerCsv("/tmp/veiculos.csv", &n);
  if (!veiculos)
    return 1;

  Veiculo selecionados[1000];
  int num_selecionados = 0;
  char input[50];

  while (scanf("%s", input) == 1 && strcmp(input, "-1") != 0) {
    int id_busca = atoi(input);

    for (int i = 0; i < n; i++) {
      if (veiculos[i].id == id_busca) {
        selecionados[num_selecionados++] = veiculos[i];
        break;
      }
    }
  }

  for (int i = 0; i < num_selecionados - 1; i++) {
    int menor = i;
    for (int j = i + 1; j < num_selecionados; j++) {
      if (strcmpIgnoreCase(selecionados[j].modelo, selecionados[menor].modelo) <
          0) {
        menor = j;
      }
    }
    Veiculo temp = selecionados[menor];
    selecionados[menor] = selecionados[i];
    selecionados[i] = temp;
  }

  for (int i = 0; i < num_selecionados; i++) {
    char buffer[500];
    formatVeiculo(&selecionados[i], buffer, sizeof(buffer));
    printf("%s\n", buffer);
  }

  free(veiculos);
  return 0;
}

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

void selectionSort(Veiculo *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int menor = i;
    for (int j = i + 1; j < n; j++) {
      if (strcmp(arr[j].modelo, arr[menor].modelo) < 0) {
        menor = j;
      }
    }
    Veiculo temp = arr[menor];
    arr[menor] = arr[i];
    arr[i] = temp;
  }
}

bool pesquisaBinaria(Veiculo *arr, int n, const char *chave) {
  int esq = 0, dir = n - 1;
  while (esq <= dir) {
    int meio = esq + (dir - esq) / 2;
    int cmp = strcmp(arr[meio].modelo, chave);

    if (cmp == 0) {
      return true;
    }
    if (cmp < 0) {
      esq = meio + 1;
    } else {
      dir = meio - 1;
    }
  }
  return false;
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

  selectionSort(selecionados, num_selecionados);

  char busca[150];
  while (scanf(" %[^\r\n]", busca) == 1 && strcmp(busca, "FIM") != 0) {
    if (pesquisaBinaria(selecionados, num_selecionados, busca)) {
      printf("SIM\n");
    } else {
      printf("NAO\n");
    }
  }

  free(veiculos);
  return 0;
}

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
  char line[2048];

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

typedef struct Celula {
  Veiculo elemento;
  struct Celula *prox;
} Celula;

Celula *primeiro;
Celula *ultimo;
int tamanhoLista;

Celula *novaCelula(Veiculo elemento) {
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->elemento = elemento;
  nova->prox = NULL;
  return nova;
}

void start() {
  Veiculo dummy;
  memset(&dummy, 0, sizeof(Veiculo));
  primeiro = novaCelula(dummy);
  ultimo = primeiro;
  tamanhoLista = 0;
}

void inserirInicio(Veiculo x) {
  Celula *tmp = novaCelula(x);
  tmp->prox = primeiro->prox;
  primeiro->prox = tmp;
  if (primeiro == ultimo)
    ultimo = tmp;
  tamanhoLista++;
}

void inserirFim(Veiculo x) {
  ultimo->prox = novaCelula(x);
  ultimo = ultimo->prox;
  tamanhoLista++;
}

void inserir(Veiculo x, int pos) {
  if (pos < 0 || pos > tamanhoLista)
    return;
  if (pos == 0) {
    inserirInicio(x);
  } else if (pos == tamanhoLista) {
    inserirFim(x);
  } else {
    Celula *i = primeiro;
    for (int j = 0; j < pos; j++, i = i->prox)
      ;
    Celula *tmp = novaCelula(x);
    tmp->prox = i->prox;
    i->prox = tmp;
    tamanhoLista++;
  }
}

Veiculo removerInicio() {
  if (primeiro == ultimo) {
    Veiculo vazia;
    memset(&vazia, 0, sizeof(Veiculo));
    return vazia;
  }
  Celula *tmp = primeiro->prox;
  primeiro->prox = tmp->prox;
  Veiculo resp = tmp->elemento;
  if (ultimo == tmp)
    ultimo = primeiro;
  free(tmp);
  tamanhoLista--;
  return resp;
}

Veiculo removerFim() {
  if (primeiro == ultimo) {
    Veiculo vazia;
    memset(&vazia, 0, sizeof(Veiculo));
    return vazia;
  }
  Celula *i;
  for (i = primeiro; i->prox != ultimo; i = i->prox)
    ;
  Veiculo resp = ultimo->elemento;
  ultimo = i;
  free(ultimo->prox);
  ultimo->prox = NULL;
  tamanhoLista--;
  return resp;
}

Veiculo remover(int pos) {
  if (primeiro == ultimo || pos < 0 || pos >= tamanhoLista) {
    Veiculo vazia;
    memset(&vazia, 0, sizeof(Veiculo));
    return vazia;
  }
  if (pos == 0)
    return removerInicio();
  if (pos == tamanhoLista - 1)
    return removerFim();

  Celula *i = primeiro;
  for (int j = 0; j < pos; j++, i = i->prox)
    ;
  Celula *tmp = i->prox;
  Veiculo resp = tmp->elemento;
  i->prox = tmp->prox;
  free(tmp);
  tamanhoLista--;
  return resp;
}

void mostrar() {
  int pos = 0;
  for (Celula *i = primeiro->prox; i != NULL; i = i->prox) {
    char buffer[1024];
    formatVeiculo(&(i->elemento), buffer, sizeof(buffer));
    printf("%s\n", buffer);
  }
}

Veiculo *buscarVeiculo(Veiculo *veiculos, int n, int id) {
  for (int i = 0; i < n; i++) {
    if (veiculos[i].id == id)
      return &veiculos[i];
  }
  return NULL;
}

int main() {
  int totalVeiculos = 0;
  Veiculo *bancoVeiculos = lerCsv("/tmp/veiculos.csv", &totalVeiculos);

  start();
  char input[50];

  while (scanf("%s", input) == 1 && strcmp(input, "-1") != 0) {
    int idBusca = atoi(input);
    Veiculo *v = buscarVeiculo(bancoVeiculos, totalVeiculos, idBusca);
    if (v)
      inserirFim(*v);
  }

  int numOperacoes;
  if (scanf("%d", &numOperacoes) != 1)
    return 0;

  for (int i = 0; i < numOperacoes; i++) {
    char comando[5];
    scanf("%s", comando);

    if (strcmp(comando, "II") == 0) {
      int id;
      scanf("%d", &id);
      Veiculo *v = buscarVeiculo(bancoVeiculos, totalVeiculos, id);
      if (v)
        inserirInicio(*v);

    } else if (strcmp(comando, "I*") == 0) {
      int pos, id;
      scanf("%d %d", &pos, &id);
      Veiculo *v = buscarVeiculo(bancoVeiculos, totalVeiculos, id);
      if (v)
        inserir(*v, pos);

    } else if (strcmp(comando, "IF") == 0) {
      int id;
      scanf("%d", &id);
      Veiculo *v = buscarVeiculo(bancoVeiculos, totalVeiculos, id);
      if (v)
        inserirFim(*v);

    } else if (strcmp(comando, "RI") == 0) {
      Veiculo rem = removerInicio();
      if (rem.id != 0)
        printf("(R)%s %s\n", rem.marca, rem.modelo);

    } else if (strcmp(comando, "R*") == 0) {
      int pos;
      scanf("%d", &pos);
      Veiculo rem = remover(pos);
      if (rem.id != 0)
        printf("(R)%s %s\n", rem.marca, rem.modelo);

    } else if (strcmp(comando, "RF") == 0) {
      Veiculo rem = removerFim();
      if (rem.id != 0)
        printf("(R)%s %s\n", rem.marca, rem.modelo);
    }
  }

  mostrar();

  free(bancoVeiculos);
  while (primeiro != ultimo)
    removerInicio();
  free(primeiro);

  return 0;
}

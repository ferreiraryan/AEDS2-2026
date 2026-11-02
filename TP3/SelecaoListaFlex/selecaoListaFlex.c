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

typedef struct Celula {
  Veiculo *elemento;
  struct Celula *prox;
} Celula;

typedef struct {
  Celula *inicio;
  Celula *fim;
  int tamanho;
} Lista;

Celula *criarCelula(Veiculo *v) {
  Celula *n = (Celula *)malloc(sizeof(Celula));
  n->elemento = v;
  n->prox = NULL;
  return n;
}

void inicializar(Lista *lista) {
  lista->inicio = (Celula *)malloc(sizeof(Celula));
  lista->fim = lista->inicio;
  lista->tamanho = 0;
}

void inserirFim(Lista *lista, Veiculo *v) {
  Celula *n = criarCelula(v);
  lista->fim->prox = n;
  lista->fim = n;
  lista->tamanho++;
}

int estaVazia(const Lista *lista) {
  return lista->inicio == lista->fim ? 1 : 0;
}

Data parseData(char *s) {
  Data d = {0};
  sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
  return d;
}

void formatData(Data d, char *buffer) {
  sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

Veiculo *parseVeiculo(char *s) {
  Veiculo *v = malloc(sizeof(Veiculo));
  if (!v)
    return NULL;
  memset(v, 0, sizeof(Veiculo));

  char buffCombustivel[200] = {0};
  char strTurbo[10] = {0};
  char strData[30] = {0};

  sscanf(
      s,
      "%d,%[^,],%[^,],%d,%[^,],%[^,],%d,%lf,%[^,],%[^,],%lf,%lf,%lf,%[^,],%s",
      &v->id, v->marca, v->modelo, &v->ano, v->categoria, buffCombustivel,
      &v->cilindros, &v->cilindrada, v->transmissao, v->tracao,
      &v->consumoCidade, &v->consumoEstrada, &v->co2, strTurbo, strData);

  char *limpo = buffCombustivel;
  if (limpo[0] == '[')
    limpo++;
  if (strlen(limpo) > 0 && limpo[strlen(limpo) - 1] == ']') {
    limpo[strlen(limpo) - 1] = '\0';
  }

  int i = 0;
  char *token = strtok(limpo, ";");
  while (token != NULL && i < 10) {
    strcpy(v->combustivel[i], token);
    i++;
    token = strtok(NULL, ";");
  }

  v->turbo = (strcmp(strTurbo, "true") == 0);
  v->dataRegistro = parseData(strData);

  return v;
}

void formatVeiculo(Veiculo *v, char *buffer) {
  char dataStr[30];
  formatData(v->dataRegistro, dataStr);

  char combStr[200] = {0};
  for (int i = 0; i < 10 && strlen(v->combustivel[i]) > 0; i++) {
    if (i > 0)
      strcat(combStr, ",");
    strcat(combStr, v->combustivel[i]);
  }

  sprintf(
      buffer,
      "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f "
      "## %.2f ## %.1f ## %s ## %s]",
      v->id, v->marca, v->modelo, v->ano, v->categoria, combStr, v->cilindros,
      v->cilindrada, v->transmissao, v->tracao, v->consumoCidade, v->consumoEstrada,
      v->co2, v->turbo ? "true" : "false", dataStr);
}

Lista *lerCsv(char *caminhoArquivo) {
  FILE *f = fopen(caminhoArquivo, "r");
  if (!f) {
    return NULL;
  }

  Lista *l = (Lista *) malloc(sizeof(Lista));

  inicializar(l);

  char line[1024];
  fgets(line, sizeof(line), f);

  while (fgets(line, sizeof(line), f)) {
    line[strcspn(line, "\r\n")] = '\0';

    Veiculo *v = parseVeiculo(line);
    if (v) {
      inserirFim(l, v);
    }
  }

  fclose(f);

  return l;
}



void selectionSort(Lista *l){
    for (Celula *i = l->inicio->prox; i !=NULL; i = i->prox) {
      Celula *menor = i;
      for (Celula *j = i->prox; j !=NULL; j = j->prox) {
      
        int cmp = strcasecmp(j->elemento->modelo, menor->elemento->modelo);
        if (cmp < 0 ) {
            menor = j;
        }
      }



        if(menor!=i){
          Veiculo *tmp = i->elemento;
          i->elemento = menor->elemento;
          menor->elemento = tmp;
        }
    }
}

int main() {
  Lista *lista = lerCsv("/tmp/veiculos.csv");

  Lista *selecionados = (Lista *)malloc(sizeof(Lista));
  inicializar(selecionados);

  if (estaVazia(lista)) {
    return 1;
  }

  int idBusca;
  while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
    for (Celula *i = lista->inicio->prox; i !=NULL; i = i->prox) {
      if (i->elemento->id == idBusca) {
        inserirFim(selecionados, i->elemento);
        break;
      }
    }
  }

  selectionSort(selecionados);

  for (Celula *i = selecionados->inicio->prox; i !=NULL; i = i->prox) {
    char buff[1024];
    formatVeiculo(i->elemento, buff);
    printf("%s\n", buff);
  }
  free(lista);
  return 0;
}

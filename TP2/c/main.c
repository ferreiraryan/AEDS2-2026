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
  char marca[50];
  int ano;
  char categoria[50];
  char combustivel[50][50];
  int cilindros;
  double cilindrada;
  char transmissao[50];
  char tracao[50];
  double consumoCidade;
  double consumoEstrada;
  double co2;
  bool turbo;
  Data dataRegistro;

} Veiculo;

void formatData(Data d, char *buffer) {
  sprintf(buffer, "%d/%d/%d", d.dia, d.mes, d.ano);
}
Data parseData(char *s) {
  int dia, mes, ano;
  sscanf(s, "%d/%d/%d", &dia, &mes, &ano);
  Data *aux = (Data *)malloc(sizeof(Data));
  aux->dia = dia;
  aux->mes = mes;
  aux->ano = ano;
  return *aux;
}
void formatVeiculo(Veiculo *v, char *buffer, int size) {
  char strCombustiveis[256] = "";

  for (int i = 0; i < 50; i++) {
    if (v->combustivel[i][0] == '\0') {
      break;
    }
    if (i > 0) {
      strcat(strCombustiveis, ", ");
    }
    strcat(strCombustiveis, v->combustivel[i]);
  }

  snprintf(buffer, size,
           "[%d ## %s ## %d ## %s ## [%s] ## %d ## "
           "%.1f ## %s ## %s ## %.1f ## %.1f ## %.1f ## "
           "%s ## %02d/%02d/%04d]",
           v->id, v->marca, v->ano, v->categoria, strCombustiveis, v->cilindros,
           v->cilindrada, v->transmissao, v->tracao, v->consumoCidade,
           v->consumoEstrada, v->co2, v->turbo ? "Sim" : "Nao",
           v->dataRegistro.dia, v->dataRegistro.mes, v->dataRegistro.ano);
}

Data parseVeiculo(char *v) {
  int dia, mes, ano;
  sscanf(v, "%d/%d/%d", &dia, &mes, &ano);
  Veiculo *aux = (Veiculo *)malloc(sizeof(Veiculo));
  return *aux;
}

int main() {
  Veiculo meuCarro = {.id = 1,
                      .marca = "Toyota Corolla",
                      .ano = 2024,
                      .categoria = "Sedan",
                      .combustivel = "Flex",
                      .cilindros = 4,
                      .cilindrada = 2.0,
                      .transmissao = "CVT",
                      .tracao = "Dianteira",
                      .consumoCidade = 11.6,
                      .consumoEstrada = 13.9,
                      .co2 = 102.5,
                      .turbo = false,
                      .dataRegistro = {.dia = 14, .mes = 9, .ano = 2026}};

  meuCarro.dataRegistro = parseData("10/12/2000");

  char buffer[11];
  formatData(meuCarro.dataRegistro, buffer);
  printf("%s\n", buffer);

  char buffCarr[200];
  formatVeiculo(&meuCarro, buffCarr, 200);

  printf("%s\n", buffCarr);
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

struct fatia
{
  int valor;
  struct fatia *ant;
  struct fatia *prox;
};
typedef struct fatia Fatia;

typedef struct
{
  Fatia *fatia;
  int tamanho;
  int valorAcumulado;
} Roda;

// Metodos de deque
Roda *criaRoda(void);
bool inserirRodaFim(Roda *roda, int valor);
void exibirRoda(Roda *roda);
void reinicializarRoda(Roda *roda);

// Funcoes do jogo
void exibirCabecallho(void);
void jogar(Roda *roda);
int girarRoda(Roda *roda);

int main(void)
{
  int opcao, i;

  Roda *roda = criaRoda();
  for (i = 0; i < 15; i++)
    inserirRodaFim(roda, rand() % 1000);

  do
  {

    if (!opcao)
    {
      exibirCabecallho();
      printf("Digite 1 para comecar a jogar: ");
    }
    else
    {
      jogar(roda);
      printf("Voce gostaria de jogar novamente?\n");
      printf("1 - Sim\n");
      printf("0 - Nao\n");
      printf("Opcao: ");
    }
    scanf("%d", &opcao);
  } while (opcao != 0);

  reinicializarRoda(roda);
}

Roda *criaRoda(void)
{
  Roda *roda = (Roda *)malloc(sizeof(Roda));
  roda->fatia = (Fatia *)malloc(sizeof(Fatia));
  roda->fatia->prox = roda->fatia;
  roda->fatia->ant = roda->fatia;
  roda->tamanho = 0;
  roda->valorAcumulado = 0;
  return roda;
}

bool inserirRodaFim(Roda *roda, int valor)
{
  if (roda->tamanho == 0)
  {
    roda->fatia->valor = valor;
  }
  else
  {
    Fatia *novo = (Fatia *)malloc(sizeof(Fatia));
    novo->valor = valor;
    novo->prox = roda->fatia;
    novo->ant = roda->fatia->ant;
    novo->ant->prox = novo;
    novo->prox->ant = novo;
  }
  roda->tamanho++;
  return true;
}

void exibirCabecallho()
{
  printf("---------------------------------------------\n");
  printf("              Roda da Fortuna\n");
  printf("---------------------------------------------\n\n");
}

void jogar(Roda *roda)
{
  int valorGanho = girarRoda(roda);

  system("CLS");
  exibirCabecallho();
  exibirRoda(roda);

  roda->valorAcumulado += valorGanho;
  printf("Valor ganho: %d \n", valorGanho);
  printf("Valor acumulado: %d \n\n", roda->valorAcumulado);
}

int girarRoda(Roda *roda)
{
  int forca, i;

  forca = rand() % roda->tamanho;
  for (i = 0; i < forca; i++)
    roda->fatia = roda->fatia->prox;

  return roda->fatia->valor;
}

void exibirRoda(Roda *roda)
{
  int i;
  Fatia *inicio = roda->fatia;

  printf("Esta eh a roda atual: \n");
  do
  {
    printf("%i ", roda->fatia->valor);
    roda->fatia = roda->fatia->prox;
  } while (roda->fatia != inicio);
  printf("\n\n");
}

void reinicializarRoda(Roda *roda)
{
  Fatia *fatia = roda->fatia->prox;
  while (fatia != roda->fatia)
  {
    Fatia *apagar = fatia;
    fatia = fatia->prox;
    free(apagar);
  }
  roda->fatia->prox = roda->fatia;
  roda->fatia->ant = roda->fatia;
}
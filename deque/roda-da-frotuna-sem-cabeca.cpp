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
  Fatia *cabeca;
  int ultimaPosicao;
  int valorAcumulado;
} Roda;

// Metodos de deque
Roda *criaRoda(void);
bool inserirRodaFim(Roda *roda, int valor);
void exibirRodaAtual(Roda *roda);
void reinicializarRoda(Roda *roda);

// Funcoes do jogo
void exibirCabecallho();
void jogar(Roda *roda);
int girarRoda(Roda *roda);
Fatia *ultimaPosicao(Roda *roda);

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
  roda->cabeca = (Fatia *)malloc(sizeof(Fatia));
  roda->cabeca->prox = roda->cabeca;
  roda->cabeca->ant = roda->cabeca;
  roda->ultimaPosicao = 1;
  roda->valorAcumulado = 0;
  return roda;
}

bool inserirRodaFim(Roda *roda, int valor)
{
  Fatia *novo = (Fatia *)malloc(sizeof(Fatia));
  novo->valor = valor;
  novo->prox = roda->cabeca;
  novo->ant = roda->cabeca->ant;
  novo->ant->prox = novo;
  novo->prox->ant = novo;
  return true;
}

void exibirCabecallho()
{
  printf("---------------------------------------------\n");
  printf("       Roda da Fortuna\n");
  printf("---------------------------------------------\n\n");
}

void jogar(Roda *roda)
{
  int valorGanho = girarRoda(roda);

  system("CLS");
  exibirCabecallho();
  exibirRodaAtual(roda);

  roda->valorAcumulado += valorGanho;
  printf("Valor ganho: %d \n", valorGanho);
  printf("Valor acumulado: %d \n\n", roda->valorAcumulado);
}

int girarRoda(Roda *roda)
{
  int forca = (rand() % 15) + roda->ultimaPosicao;
  int contador = 0;
  Fatia *fatiaSelecionada = roda->cabeca->prox;

  while (contador < forca)
  {
    if (fatiaSelecionada != roda->cabeca)
      contador++;
    fatiaSelecionada = fatiaSelecionada->prox;
  }

  while (forca > 15)
    forca -= 15;

  roda->ultimaPosicao = forca;

  return fatiaSelecionada->valor;
}

void exibirRodaAtual(Roda *roda)
{
  printf("Esta eh a roda atual: \n");
  Fatia *fatia = ultimaPosicao(roda);

  int contador = 0;
  while (contador < 15)
  {
    if (fatia != roda->cabeca)
    {
      contador++;
      printf("%i ", fatia->valor);
    }
    fatia = fatia->prox;
  }
  printf("\n\n");
}

Fatia *ultimaPosicao(Roda *roda)
{
  Fatia *fatia = roda->cabeca->prox;
  int contador = 0;

  while (contador < roda->ultimaPosicao)
  {
    fatia = fatia->prox;
    contador++;
  }

  return fatia;
}

void reinicializarRoda(Roda *roda)
{
  Fatia *end = roda->cabeca->prox;
  while (end != roda->cabeca)
  {
    Fatia *apagar = end;
    end = end->prox;
    free(apagar);
  }
  roda->cabeca->prox = roda->cabeca;
  roda->cabeca->ant = roda->cabeca;
}

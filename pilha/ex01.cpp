#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 50

typedef struct pilha
{
  int n;
  float vet[MAX];
} Pilha;

Pilha *cria(void);
Pilha *push(Pilha *p, float v);
Pilha *pop(Pilha *p);
int vazia(Pilha *p);
void libera(Pilha *p);
void escreve(Pilha *p);
int menu();
void opcao(Pilha *p, int opt);
void transfere(Pilha *p);
void transfereIgual(Pilha *p);

int main()
{
  int opt;
  Pilha *P;

  // Cria a pilha
  P = cria();

  P = push(P, 10);
  escreve(P);
  P = push(P, 11);
  P = push(P, 33);
  escreve(P);

  P = pop(P);
  escreve(P);

  do
  {
    opt = menu();
    opcao(P, opt);
  } while (opt);

  getch();
}

int menu()
{
  int opt;
  printf("Escolha a opcao\n");
  printf("0. Sair\n");
  printf("1. Transfere\n");
  printf("2. Transfere Igual\n");
  printf("Opcao: ");
  scanf("%d", &opt);
  return opt;
}

void opcao(Pilha *PILHA, int opt)
{
  switch (opt)
  {
  case 0:
    libera(PILHA);
    break;

  case 1:
    transfere(PILHA);
    getch();
    break;

  case 2:
    transfereIgual(PILHA);
    getch();
    break;
  default:
    printf("Comando invalido....\n\n");
    getch();
  }
}

void transfere(Pilha *p)
{
  Pilha *nova = cria();

  if (vazia(p))
  {
    printf("Pilha vazia.\n");
    exit(1); /* aborta programa */
  }

  do
  {
    p->n--;
    nova->vet[nova->n] = p->vet[p->n];
    nova->n++;
  } while (p->n > 0);

  escreve(p);
  escreve(nova);
  exit(1); /* aborta programa */
}

void transfereIgual(Pilha *p)
{
  Pilha *nova = cria();

  if (vazia(p))
  {
    printf("Pilha vazia.\n");
    exit(1); /* aborta programa */
  }

  p->n = 0;
  do {
    nova->vet[nova->n] = p->vet[p->n];
    nova->n++;
    p->n++;
  } while (p->vet[p->n] != NULL);

  escreve(p);
  escreve(nova);
  exit(1); /* aborta programa */
}

Pilha *cria(void)
{
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  p->n = 0; /* inicializa com zero elementos */
  return p;
}

Pilha *push(Pilha *p, float v)
{
  if (p->n == MAX)
  { /* capacidade esgotada */
    printf("Capacidade da pilha estourou.\n");
    exit(1); /* aborta programa */
  }

  /* insere elemento na pr�xima posi��o livre */
  p->vet[p->n] = v;
  p->n++;
  return p;
}

Pilha *pop(Pilha *p)
{
  if (vazia(p))
  {
    printf("Pilha vazia.\n");
    exit(1); /* aborta programa */
  }
  /* retira elemento do topo */
  p->vet[p->n - 1] = 0.0;
  p->n--;
  return p;
}

int vazia(Pilha *p)
{
  return (p->n == 0);
}

void libera(Pilha *p)
{
  free(p);
}

void escreve(Pilha *p)
{
  int i;
  for (i = 0; i < p->n; i++)
  {
    printf("%f ", p->vet[i]);
  }
  printf("\n");
}

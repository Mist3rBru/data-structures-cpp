#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct no
{
  char letra;
  struct no *prox;
} No;

typedef struct pilha
{
  No *prim;
} Pilha;

Pilha *cria(void);
void push(Pilha *p, char v);
char pop(Pilha *p);
int vazia(Pilha *p);
void libera(Pilha *p);
void escreve(Pilha *p);
No *ins_ini(No *l, char v);
No *ret_ini(No *l);
Pilha *inverte(Pilha *p);
bool verifica(Pilha *p1, Pilha *p);

int main()
{
  Pilha *P, *P2;
  char palavra[100], letra;
  bool ehPalindromo;
  int i;

  printf("Insira uma palavra: \n");
  scanf("%s", palavra);

  P = cria();
  for (i = 0; i < 100; i++)
  {
    letra = palavra[i];
    if (letra)
      push(P, letra);
    else
      i = 100;
  }
  free(palavra);

  P2 = inverte(P);
  printf("\nNormal: ");
  escreve(P2);
  printf("\nInvertido: ");
  escreve(P);

  ehPalindromo = verifica(P, P2);
  if (ehPalindromo)
    printf("\nEh Palindromo\n");
  else
    printf("\nNao eh Palindromo\n");

  libera(P);
  libera(P2);

  getch();
}

Pilha *inverte(Pilha *p)
{
  Pilha *novaPilha = cria();
  No *no = p->prim;
  for (no = p->prim; no != NULL; no = no->prox)
  {
    push(novaPilha, no->letra);
  }
  return novaPilha;
}

bool verifica(Pilha *p, Pilha *p2)
{
  No *no = p->prim;
  No *no2 = p2->prim;
  do
  {
    if (no->letra != no2->letra)
      return false;
    no = no->prox;
    no2 = no2->prox;
  } while (no != NULL && no2 != NULL);
  return true;
}

Pilha *cria(void)
{
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  p->prim = NULL;
  return p;
}

No *ins_ini(No *l, char v)
{
  No *p = (No *)malloc(sizeof(No));
  p->letra = v;
  p->prox = l;
  return p;
}

/* fun��o auxiliar: retira do in�cio */
No *ret_ini(No *l)
{
  No *p = l->prox;
  free(l);
  return p;
}

void push(Pilha *p, char v)
{
  p->prim = ins_ini(p->prim, v);
}

char pop(Pilha *p)
{
  char v;
  if (vazia(p))
  {
    printf("Pilha vazia.\n");
    exit(1); /* aborta programa */
  }

  v = p->prim->letra;
  p->prim = ret_ini(p->prim);
  return v;
}

int vazia(Pilha *p)
{
  return (p->prim == NULL);
}

void libera(Pilha *p)
{
  No *q = p->prim;
  while (q != NULL)
  {
    No *t = q->prox;
    free(q);
    q = t;
  }
  free(p);
}

void escreve(Pilha *p)
{
  No *q;

  for (q = p->prim; q != NULL; q = q->prox)
  {
    printf("%c", q->letra);
  }
  printf("\n");
}

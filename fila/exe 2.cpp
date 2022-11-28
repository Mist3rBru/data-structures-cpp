/*
    2) Implemente um programa que receba tr�s filas: F, F_Impares e F_Pares,
    e separe todos os valores guardados em F de tal forma que
    os valores pares s�o movidos para a fila F_Pares e
    os valores �mpares s�o movidos para F_Impares.
*/

#include <stdlib.h>
#include <stdio.h>

struct no
{
    int info;
    struct no *prox;
};
typedef struct no No;

struct fila
{
    No *ini;
    No *fim;
};
typedef struct fila Fila;

No *insereFim(No *fim, int v);
No *retiraInicio(No *ini);
void insere(Fila *f, int v);
int retira(Fila *f);
int vazia(Fila *f);
void libera(Fila *f);
void ordena(Fila *forigem, Fila *fpar, Fila *fimpar);

Fila *cria(void)
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No *insereFim(No *fim, int v)
{
    No *p = (No *)malloc(sizeof(No));
    p->info = v;
    p->prox = NULL;
    if (fim != NULL)
        fim->prox = p;
    return p;
}

No *ret_ini(No *ini)
{
    No *p = ini->prox;
    free(ini);
    return p;
}

void insere(Fila *f, int v)
{
    f->fim = insereFim(f->fim, v);
    if (f->ini == NULL)
        f->ini = f->fim;
}

int retira(Fila *f)
{
    float v;
    if (vazia(f))
    {
        printf("Fila vazia.\n");
        exit(1);
    }
    v = f->ini->info;
    f->ini = ret_ini(f->ini);
    if (f->ini == NULL)
        f->fim = NULL;
    return v;
}

int vazia(Fila *f)
{
    return (f->ini == NULL);
}

void libera(Fila *f)
{
    No *q = f->ini;
    while (q != NULL)
    {
        No *t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}

void imprime(Fila *f)
{
    No *q;
    for (q = f->ini; q != NULL; q = q->prox)
        printf("%d\n", q->info);
}

void ordena(Fila *forigem, Fila *fpar, Fila *fimpar)
{
    int valor;

    while (!vazia(forigem))
    {
        valor = retira(forigem);
        if ((valor % 2) == 0)
            insere(fpar, valor);
        else
            insere(fimpar, valor);
    }
}

int main(void)
{
    Fila *F = cria();
    Fila *fileImpares = cria();
    Fila *filaPares = cria();

    insere(F, 100);
    insere(F, 70);
    insere(F, 60);
    insere(F, 55);
    insere(F, 43);
    insere(F, 15);
    insere(F, 5);
    insere(F, 3);
    insere(F, 1);

    ordena(F, filaPares, fileImpares);

    printf("Fila de valores impares\n");
    imprime(fileImpares);
    printf("Fila de valores pares\n");
    imprime(filaPares);

    libera(F);
    libera(fileImpares);
    libera(filaPares);

    system("pause");
    return 0;
}

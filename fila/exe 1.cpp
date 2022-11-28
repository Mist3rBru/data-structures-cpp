/*
    1) Considere a exist�ncia de duas filas A e B onde os elementos est�o ordenados da seguinte forma:
    o maior deles est� no come�o da fila e o menor no final.
    Escreva um programa que crie uma fila com os elementos das duas filas A e B tamb�m ordenados.
*/

#include <stdlib.h>
#include <stdio.h>

struct no
{
    float info;
    struct no *prox;
};
typedef struct no No;

struct fila
{
    No *ini;
    No *fim;
};
typedef struct fila Fila;

No *insereFim(No *fim, float v);
No *retiraInicio(No *ini);
void insere(Fila *f, float v);
float retira(Fila *f);
int vazia(Fila *f);
void libera(Fila *f);
void ordena(Fila *fa, Fila *fb, Fila *fc, float valorRecursivo, char filaOrigem);

Fila *cria(void)
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No *insereFim(No *fim, float v)
{
    No *p = (No *)malloc(sizeof(No));
    p->info = v;
    p->prox = NULL;
    if (fim != NULL)
        fim->prox = p;
    return p;
}

No *retiraInicio(No *ini)
{
    No *p = ini->prox;
    free(ini);
    return p;
}

void insere(Fila *f, float v)
{
    f->fim = insereFim(f->fim, v);
    if (f->ini == NULL)
        f->ini = f->fim;
}

float retira(Fila *f)
{
    float v;
    if (vazia(f))
    {
        printf("Fila vazia.\n");
        exit(1);
    }
    v = f->ini->info;
    f->ini = retiraInicio(f->ini);
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
        printf("%f\n", q->info);
}

void ordena(Fila *fa, Fila *fb, Fila *fc, float valorRecursivo, char filaOrigem)
{
    float valor, valor1;

    if (vazia(fa))
    {

        while (!vazia(fb))
        {
            valor = retira(fb);
            insere(fc, valor);
        }
    }
    else
    {
        if (vazia(fb))
        {

            while (!vazia(fa))
            {
                valor = retira(fa);
                insere(fc, valor);
            }
        }
        else
        {
            if (filaOrigem == 'a')
            {
                valor = valorRecursivo;
                valor1 = retira(fb);
            }
            else if (filaOrigem == 'b')
            {
                valor = retira(fa);
                valor1 = valorRecursivo;
            }
            else
            {
                valor = retira(fa);
                valor1 = retira(fb);
            }

            if (valor > valor1)
            {
                insere(fc, valor);
                ordena(fa, fb, fc, valor1, 'b');
            }
            else
            {
                insere(fc, valor1);
                ordena(fa, fb, fc, valor, 'a');
            }
        }
    }
}

int main(void)
{
    Fila *filaA = cria();
    Fila *filaB = cria();
    Fila *filaC = cria();

    insere(filaA, 60);
    insere(filaA, 20);
    insere(filaA, 5);
    insere(filaA, 1);

    insere(filaB, 100);
    insere(filaB, 40);
    insere(filaB, 15);
    insere(filaB, 3);

    ordena(filaA, filaB, filaC, 0, 'c');

    imprime(filaC);

    libera(filaA);
    libera(filaB);
    libera(filaC);

    system("pause");
    return 0;
}

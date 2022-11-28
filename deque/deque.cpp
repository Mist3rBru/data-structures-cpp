#include <stdio.h>
#include <malloc.h>

struct no
{
	int valor;
	struct no *ant;
	struct no *prox;
};
typedef struct no No;

typedef struct
{
	No *cabeca;
} DEQUE;

DEQUE *cria(void)
{
	DEQUE *d = (DEQUE *)malloc(sizeof(DEQUE));
	d->cabeca = (No *)malloc(sizeof(No));
	d->cabeca->prox = d->cabeca;
	d->cabeca->ant = d->cabeca;
	return d;
}

int tamanhoInicio(DEQUE *d)
{
	// Avan�ando pelo primeiro nodo
	No *inicio = d->cabeca->prox;
	int tam = 0;
	while (inicio != d->cabeca)
	{
		tam++;
		inicio = inicio->prox;
	}
	return tam;
}

int tamanhoFim(DEQUE *d)
{
	// Avan�ando pelo �ltimo nodo
	No *end = d->cabeca->ant;
	int tam = 0;
	while (end != d->cabeca)
	{
		tam++;
		end = end->ant;
	}
	return tam;
}

void exibirDequeInicio(DEQUE *d)
{
	No *inicio = d->cabeca->prox;
	printf("Deque partindo do inicio: ");
	while (inicio != d->cabeca)
	{
		printf("%i ", inicio->valor);
		inicio = inicio->prox;
	}
	printf("\n");
}

void exibirDequeFim(DEQUE *d)
{
	No *fim = d->cabeca->ant;
	printf("Deque partindo do fim: ");
	while (fim != d->cabeca)
	{
		printf("%i ", fim->valor);
		fim = fim->ant;
	}
	printf("\n");
}

bool inserirDequeInicio(DEQUE *d, int valor)
{
	No *novo = (No *)malloc(sizeof(No));
	novo->valor = valor;
	novo->prox = d->cabeca->prox;
	novo->ant = d->cabeca;
	novo->ant->prox = novo;
	novo->prox->ant = novo;
	d->cabeca->prox = novo;
	return true;
}

bool inserirDequeFim(DEQUE *d, int valor)
{
	No *novo = (No *)malloc(sizeof(No));
	novo->valor = valor;
	novo->prox = d->cabeca;
	novo->ant = d->cabeca->ant;
	novo->ant->prox = novo;
	novo->prox->ant = novo;
	return true;
}

int excluirElemDequeInicio(DEQUE *d)
{
	if (d->cabeca->prox == d->cabeca)
		return false;
	No *apagar = d->cabeca->prox;
	int valorRetorno = apagar->valor;
	d->cabeca->prox = apagar->prox;
	apagar->prox->ant = apagar->ant;
	apagar->ant->prox = apagar->prox;
	free(apagar);
	return valorRetorno;
}

int excluirElemDequeFim(DEQUE *d)
{
	if (d->cabeca->ant == d->cabeca)
		return false;
	No *apagar = d->cabeca->ant;
	int valorRetorno = apagar->valor;
	apagar->prox->ant = apagar->ant;
	apagar->ant->prox = apagar->prox;
	free(apagar);
	return valorRetorno;
}

void reinicializarDeque(DEQUE *d)
{
	No *end = d->cabeca->prox;
	while (end != d->cabeca)
	{
		No *apagar = end;
		end = end->prox;
		free(apagar);
	}
	d->cabeca->prox = d->cabeca;
	d->cabeca->ant = d->cabeca;
}

int main(void)
{
	int valorRemovido, valorInserido;

	DEQUE *deq1;
	deq1 = cria();

	valorInserido = 23;
	inserirDequeFim(deq1, valorInserido);
	printf("Valor inserido no fim: %d\n", valorInserido);

	valorInserido = 15;
	inserirDequeFim(deq1, valorInserido);
	printf("Valor inserido no fim: %d\n", valorInserido);

	exibirDequeFim(deq1);
	printf("Tamanho do deque contando do fim: %d\n", tamanhoFim(deq1));

	valorRemovido = excluirElemDequeFim(deq1);
	printf("Valor removido do fim: %d\n", valorRemovido);

	exibirDequeFim(deq1);
	printf("Tamanho do deque contando do fim: %d\n", tamanhoFim(deq1));

	valorInserido = 45;
	inserirDequeInicio(deq1, valorInserido);
	printf("Valor inserido no inicio: %d\n", valorInserido);

	valorInserido = 82;
	inserirDequeInicio(deq1, valorInserido);
	printf("Valor inserido no inicio: %d\n", valorInserido);

	exibirDequeFim(deq1);
	printf("Tamanho do deque contando do fim: %d\n", tamanhoFim(deq1));

	valorRemovido = excluirElemDequeInicio(deq1);
	printf("Valor removido do inicio: %d\n", valorRemovido);

	exibirDequeFim(deq1);
	printf("Tamanho do deque contando do fim: %d\n", tamanhoFim(deq1));

	exibirDequeInicio(deq1);
	exibirDequeFim(deq1);
	printf("Tamanho do deque contando do inicio: %d\n", tamanhoInicio(deq1));
	printf("Tamanho do deque contando do fim: %d\n", tamanhoFim(deq1));

	reinicializarDeque(deq1);
}

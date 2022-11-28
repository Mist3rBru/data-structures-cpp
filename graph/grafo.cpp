#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;
int MAX_GRAPH_SIZE = 20;

typedef struct Vertice
{
	int id;
	int nArestas;
	struct Aresta **aresta;
} Vertice;

typedef struct Aresta
{
	char peso;
	Vertice *vertice;
} Aresta;

typedef struct Grafo
{
	int tamanho;
	Vertice **vertice;
} Grafo;

typedef struct Historico
{
	int nFilas;
	Fila **fila;
	int nVertices;
	Vertice **vertice;
} Historico;

typedef struct Rota
{
	char peso;
	int de;
	int para;
} Rota;

typedef struct Fila
{
	int peso;
	bool chegou;
	int nRotas;
	Rota **rota;
} Fila;

// Arquivo
void lerArquivo(Grafo *grafo);

// Vertice
Vertice *criaVertice(int id);
Vertice *encontraVertice(Grafo *grafo, int id);
Vertice *encontraOuCriaVertice(Grafo *grafo, int id);
void insereVertice(Grafo *grafo, int id, string arestas);

// Aresta
Aresta *criaAresta(char peso, Vertice *vertice);
void insereAresta(Vertice *origem, Vertice *destino, char peso);

// Grafo
Grafo *criaGrafo();
void insereGrafo(Grafo *grafo, Vertice *vertice);

// Rota
Rota *criaRota(Vertice *origem, Vertice *destino, int peso);
// void exibirRota(Rota *rota);

// Menu
void exibirMenu(Grafo *grafo);

int main(void)
{
	Grafo *grafo = criaGrafo();

	lerArquivo(grafo);

	exibirMenu(grafo);

	return 0;
}

void exibirMenu(Grafo *grafo)
{
	int inicio, fim, option;
	do
	{
		printf("\nInsira o vertice de origem: ");
		scanf("%i", &inicio);
		printf("Insira o vertice de destino: ");
		scanf("%i", &fim);

		printf("\nInsira '1' para continuar;\n");
		printf("Insira '0' para encerrar;\n");
		printf("Digite uma opcao: ");
		scanf("%i", &option);
	} while (option != 0);
}

// Arquivo
void lerArquivo(Grafo *grafo)
{
	int i = 0;
	string linha;
	ifstream arquivo;
	arquivo.open("dados.txt", ios::in);

	if (arquivo.is_open())
	{
		printf("Lendo Arquivo ...\n");
		while (getline(arquivo, linha))
		{
			cout << "\nLinha " << i << ": " << linha << endl;
			insereVertice(grafo, i, linha);
			i++;
		}
		arquivo.close();
		printf("\nArquivo lido com sucesso. \n");
		printf("\n----------------------------------\n");
	}
	else
	{
		printf("Arquivo não encontrado :( \n");
		exit(1);
	}
}

Vertice *criaVertice(int id)
{
	Vertice *vertice = (Vertice *)malloc(sizeof(Vertice));
	vertice->id = id;
	vertice->aresta = (Aresta **)malloc(MAX_GRAPH_SIZE * sizeof(Aresta *));
	vertice->nArestas = 0;
	printf("Vertice: %d criado\n", id);
	return vertice;
}

// Vertice
Vertice *encontraVertice(Grafo *grafo, int id)
{
	for (int i = 0; i < grafo->tamanho; i++)
		if (grafo->vertice[i]->id == id)
			return grafo->vertice[i];

	printf("Vertice: %d nao encontrado\n", id);
	return NULL;
}

Vertice *encontraOuCriaVertice(Grafo *grafo, int id)
{
	Vertice *vertice = encontraVertice(grafo, id);
	if (vertice == NULL)
		vertice = criaVertice(id);
	return vertice;
}

void insereVertice(Grafo *grafo, int id, string arestas)
{
	Vertice *vertice = encontraOuCriaVertice(grafo, id);
	insereGrafo(grafo, vertice);

	int i = 0;
	char peso = arestas[0];
	while (peso != '\0')
	{
		if (peso != ' ')
		{
			int id = i / 2;
			Vertice *fim = encontraOuCriaVertice(grafo, id);
			insereGrafo(grafo, fim);
			insereAresta(vertice, fim, peso);
		}
		peso = arestas[++i];
	}
}

// Aresta
Aresta *criaAresta(char peso, Vertice *vertice)
{
	Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));
	aresta->peso = peso;
	aresta->vertice = vertice;
	vertice->nArestas++;
	return aresta;
}

void insereAresta(Vertice *origem, Vertice *destino, char peso)
{
	Aresta *aresta = criaAresta(peso, destino);
	if (origem->id != destino->id && peso != '0')
	{
		origem->aresta[origem->nArestas] = aresta;
		origem->nArestas++;
		printf("Aresta adicionada de %d ate %d\n", origem->id, destino->id);
	}
}

// Grafo
Grafo *criaGrafo()
{
	Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
	grafo->tamanho = 0;
	grafo->vertice = (Vertice **)malloc(MAX_GRAPH_SIZE * sizeof(Vertice));
	return grafo;
}

void insereGrafo(Grafo *grafo, Vertice *vertice)
{
	bool repetido = false;

	for (int i = 0; i < grafo->tamanho; i++)
		if (grafo->vertice[i]->id == vertice->id)
			repetido = true;

	if (!repetido)
	{
		grafo->vertice[grafo->tamanho] = vertice;
		grafo->tamanho++;
		printf("Vertice: %d adicionado a grafo | %d\n", vertice->id, grafo->tamanho);
	}
}

// Rota
Rota *criaRota(Vertice *origem, Vertice *destino, int peso)
{
	Rota *rota = (Rota *)malloc(sizeof(Rota));
	rota->peso = peso;
	rota->de = origem->id;
	rota->para = destino->id;
	return rota;
}

// Fila
Fila *criaFila()
{
	Fila *fila = (Fila *)malloc(sizeof(Fila));
	fila->chegou = false;
	fila->nRotas = 0;
	fila->rota = (Rota **)malloc(MAX_GRAPH_SIZE * sizeof(Rota));
	fila->peso = 0;
}

void herdaFila(Fila *pai, Fila *filha)
{
	filha->peso = pai->peso;
	filha->nRotas = pai->nRotas;
	filha->rota = pai->rota;
}

void insereFila(Fila *fila, Rota *rota)
{
	fila->rota[fila->nRotas] = rota;
	fila->nRotas++;
	fila->peso += rota->peso;
}

// Historico
Historico *criaHistorico()
{
	Historico *historico = (Historico *)malloc(sizeof(Historico));
	historico->nFilas = 0;
	historico->fila = (Fila **)malloc(MAX_GRAPH_SIZE * sizeof(Fila));
	historico->nVertices = 0;
	historico->vertice = (Vertice **)malloc(MAX_GRAPH_SIZE * sizeof(Vertice));
}

void insereHistorico(Historico *historico, Fila *fila, Vertice *origem)
{
	historico->fila[historico->nFilas] = fila;
	historico->nFilas++;

	bool repetido = false;
	for (int i = 0; i < historico->nVertices; i++)
		if (historico->vertice[i]->id == origem->id)
			repetido = true;

	if (!repetido)
	{
		historico->vertice[historico->nVertices] = origem;
		historico->nVertices++;
	}
}

void percorreFila(Fila *fila, Vertice *origem, Vertice *destino, int nRota, Historico *historico)
{
	if (origem->nArestas > nRota)
	{
		Fila *novaFila = criaFila();
		herdaFila(fila, novaFila);
		insereHistorico(historico, novaFila, origem);
		percorreFila(novaFila, origem, destino, nRota + 1, historico);
	}

	while (origem != NULL && origem->id != destino->id)
	{
		Rota *rota = criaRota(origem, origem->aresta[nRota]->vertice, origem->aresta[nRota]->peso);
		insereFila(fila, rota);
		percorreFila(fila, origem->aresta[0]->vertice, destino, 0, historico);
		origem = origem->aresta[nRota]->vertice;
	}
}
// void exibirRota(Vertice *rota)
// {
// 	Vertice *inicio = rota;
// 	printf("\n");
// 	if (inicio->aresta == NULL)
// 		printf("Nenhuma aresta foi encontrado :(\n");
// 	else
// 		do
// 		{
// 			printf("De %d percorre %c ate %d\n", inicio->id, inicio->aresta->peso, inicio->aresta->vertice->id);
// 			inicio = inicio->aresta->vertice;
// 		} while (inicio->aresta != NULL && inicio->aresta->vertice->id != rota->id);
// }

// Fila
Fila *criaFila()
{
	Fila *fila = (Fila *)malloc(sizeof(Fila));
	fila->chegou = false;
	fila->peso = 0;
	fila->rota = NULL;
	fila->historico = NULL;
}

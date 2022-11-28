#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;
int MAX_GRAPH_SIZE = 100;

typedef struct Vertice
{
	int id;
	int nArestas;
	struct Aresta **aresta;
} Vertice;

typedef struct Aresta
{
	int peso;
	Vertice *vertice;
} Aresta;

typedef struct Grafo
{
	int tamanho;
	Vertice **vertice;
} Grafo;

typedef struct Rota
{
	int peso;
	Vertice *de;
	Vertice *para;
} Rota;

typedef struct Fila
{
	int peso;
	bool chegou;
	int nRotas;
	Rota **rota;
} Fila;

typedef struct Historico
{
	Vertice *origem;
	Vertice *destino;
	int nFilas;
	Fila **fila;
} Historico;

// Arquivo
void lerArquivo(Grafo *grafo);

// Vertice
Vertice *criaVertice(int id);
Vertice *encontraVertice(Grafo *grafo, int id);
Vertice *encontraOuCriaVertice(Grafo *grafo, int id);
void insereVertice(Grafo *grafo, int id, string arestas);
void excluiVertice(Vertice *vertice);

// Aresta
Aresta *criaAresta(int peso, Vertice *vertice);
void insereAresta(Vertice *origem, Vertice *destino, int peso);

// Grafo
Grafo *criaGrafo();
void insereGrafo(Grafo *grafo, Vertice *vertice);
void excluiGrafo(Grafo *grafo);

// Rota
Rota *criaRota(Vertice *origem, Aresta *aresta);

// Fila
Fila *criaFila();
Fila *criaFilaHerdeira(Fila *pai);
void insereFila(Fila *fila, Rota *rota);
void percorreFila(Fila *fila, Vertice *origem, int nAresta, Historico *historico);
Fila *melhorFila(Historico *historico);
void excluiFila(Fila *fila);

// Historico
Historico *criaHistorico(Vertice *origem, Vertice *destino);
void insereFilaHistorico(Historico *historico, Fila *fila);
void excluiHistorico(Historico *historico);

// Utils
int charParaInt(char c);

// Servicos
void encontraMenorCaminho(Grafo *grafo, int inicio, int fim);

// Menu
void exibirMenu(Grafo *grafo);

int main(void)
{
	Grafo *grafo = criaGrafo();

	lerArquivo(grafo);
	exibirMenu(grafo);

	excluiGrafo(grafo);
	return 0;
}

void exibirMenu(Grafo *grafo)
{
	int inicio, fim, opcao;
	do
	{
		printf("\nInsira o vertice de origem: ");
		scanf("%i", &inicio);
		printf("Insira o vertice de destino: ");
		scanf("%i", &fim);

		encontraMenorCaminho(grafo, inicio, fim);

		printf("\nInsira '1' para continuar;\n");
		printf("Insira '0' para encerrar;\n");
		printf("Digite uma opcao: ");
		scanf("%i", &opcao);
	} while (opcao != 0);
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

void excluiVertice(Vertice *vertice)
{
	for (int i = 0; i < vertice->nArestas; i++)
		free(vertice->aresta[i]);

	free(vertice);
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
			insereAresta(vertice, fim, charParaInt(peso));
		}
		peso = arestas[++i];
	}
}

// Aresta
Aresta *criaAresta(int peso, Vertice *vertice)
{
	Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));
	aresta->peso = peso;
	aresta->vertice = vertice;
	return aresta;
}

void insereAresta(Vertice *origem, Vertice *destino, int peso)
{
	Aresta *aresta = criaAresta(peso, destino);
	if (origem->id != destino->id && peso > 0)
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

void excluiGrafo(Grafo *grafo)
{
	for (int i = 0; i < grafo->tamanho; i++)
		excluiVertice(grafo->vertice[i]);

	free(grafo);
}

// Rota
Rota *criaRota(Vertice *origem, Aresta *aresta)
{
	Rota *rota = (Rota *)malloc(sizeof(Rota));
	rota->peso = aresta->peso;
	rota->de = origem;
	rota->para = aresta->vertice;
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
	return fila;
}

Fila *criaFilaHerdeira(Fila *pai)
{
	Fila *filha = criaFila();
	filha->chegou = pai->chegou;
	filha->peso = pai->peso;
	filha->nRotas = pai->nRotas;

	for (int i = 0; i < pai->nRotas; i++)
		filha->rota[i] = pai->rota[i];
	
	// filha->rota = pai->rota;

	return filha;
}

void insereFila(Fila *fila, Rota *rota)
{
	fila->peso += rota->peso;
	fila->rota[fila->nRotas] = rota;
	fila->nRotas++;
}

void percorreFila(Fila *fila, Vertice *origem, int nAresta, Historico *historico)
{
	if (origem->id == historico->destino->id || fila->chegou == true)
	{
		fila->chegou = true;
		return;
	}

	if (origem->nArestas > nAresta + 1)
	{
		Fila *novaFila = criaFilaHerdeira(fila);
		insereFilaHistorico(historico, novaFila);
		percorreFila(novaFila, origem, nAresta + 1, historico);
	}

	if (origem->nArestas >= nAresta + 1)
	{
		Aresta *aresta = origem->aresta[nAresta];
		if (aresta->vertice->id != historico->origem->id)
		{
			Rota *rota = criaRota(origem, aresta);
			insereFila(fila, rota);
			percorreFila(fila, rota->para, 0, historico);
		}
	}
}

Fila *melhorFila(Historico *historico)
{
	Fila *melhor = historico->fila[0];

	for (int i = 0; i < historico->nFilas; i++)
		if (historico->fila[i]->chegou == true)
			if (melhor->chegou == false || historico->fila[i]->peso < melhor->peso)
				melhor = historico->fila[i];

	if (melhor->chegou == false)
		return NULL;

	return melhor;
}

void excluiFila(Fila *fila)
{
	// for (int i = 0; i < fila->nRotas; i++)
	// 	free(fila->rota[i]);

	free(fila);
}

// Historico
Historico *criaHistorico(Vertice *origem, Vertice *destino)
{
	Historico *historico = (Historico *)malloc(sizeof(Historico));
	historico->nFilas = 0;
	historico->fila = (Fila **)malloc(MAX_GRAPH_SIZE * sizeof(Fila));
	historico->origem = origem;
	historico->destino = destino;
	return historico;
}

void insereFilaHistorico(Historico *historico, Fila *fila)
{
	historico->fila[historico->nFilas] = fila;
	historico->nFilas++;
}

void excluiHistorico(Historico *historico)
{
	for (int i = 0; i < historico->nFilas; i++)
		excluiFila(historico->fila[i]);

	free(historico);
}

// Utils
int charParaInt(char c)
{
	return ((int)c) - ((int)'0');
}

// Servicos
void encontraMenorCaminho(Grafo *grafo, int inicio, int fim)
{
	Vertice *origem = encontraVertice(grafo, inicio);
	Vertice *destino = encontraVertice(grafo, fim);

	if (origem != NULL && destino != NULL)
		if (origem->id == destino->id)
			printf("\nVoce ja esta no vertice desejado.\n");
		else
		{
			Fila *fila = criaFila();
			Historico *historico = criaHistorico(origem, destino);
			insereFilaHistorico(historico, fila);
			percorreFila(fila, origem, 0, historico);

			Fila *melhor = melhorFila(historico);

			if (melhor != NULL)
			{
				printf("\n      ### Peso Total: %d ###\n", melhor->peso);
				for (int i = 0; i < melhor->nRotas; i++)
				{
					Rota *rota = melhor->rota[i];
					printf("-- Percorra de %d por %d unidades ate %d\n", rota->de->id, rota->peso, rota->para->id);
				}
			}
			else
				printf("\nNenhum caminho valido foi encontrado;\n");

			excluiHistorico(historico);
		}
}
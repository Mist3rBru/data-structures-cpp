#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;
int MAX_GRAPH_SIZE = 100;

typedef struct Peso
{
	int nValor;
	char valor[10];
} Peso;

typedef struct Vertice
{
	int id;
	string nome;
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

// Peso
Peso *criaPeso();
void inserePeso(Peso *peso, int valor);
void zeraPeso(Peso *peso);

// Vertice
Vertice *criaVertice(int id);
Vertice *encontraVertice(Grafo *grafo, int id);
Vertice *encontraOuCriaVertice(Grafo *grafo, int id);
Vertice *encontraVerticePorNome(Grafo *grafo, string nome);
void insereVertice(Grafo *grafo, int linha, string pesos, string vertice);

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
int charParaInt(char *c);

// Servicos
void encontraMenorCaminho(Grafo *grafo, string inicio, string fim);

int main(void)
{
	Grafo *grafo = criaGrafo();
	string inicio, fim;

	lerArquivo(grafo);

	cout << "\nInsira o nome do vertice de origem: ";
	getline(cin, inicio);
	cout << "Insira o nome do vertice de destino: ";
	getline(cin, fim);

	encontraMenorCaminho(grafo, inicio, fim);

	excluiGrafo(grafo);
	return 0;
}

// Arquivo
void lerArquivo(Grafo *grafo)
{
	int i = 0;
	string pesos, vertice;
	ifstream aPesos, aVertices;
	aPesos.open("pesos.txt", ios::in);
	aVertices.open("vertices.txt", ios::in);
	if (aPesos.is_open() && aVertices.is_open())
	{
		cout << "Lendo Grafo..." << endl;
		while (getline(aVertices, vertice) && getline(aPesos, pesos))
		{
			cout << "\nLinha " << i << ": " << pesos << endl;
			insereVertice(grafo, i, pesos, vertice);
			i++;
		}
		aPesos.close();
		aVertices.close();
		cout << "\nGrafo lido com sucesso.\n";
		cout << "\n----------------------------------\n";
	}
	else
	{
		cout << "\nGrafo não encontrado :( \n"
				 << endl;
		exit(1);
	}
}

// Peso
Peso *criaPeso()
{
	Peso *peso = (Peso *)malloc(sizeof(Peso));
	peso->nValor = 0;
	peso->valor[0] = '\0';
	return peso;
}

void inserePeso(Peso *peso, char valor)
{
	peso->valor[peso->nValor] = valor;
	peso->nValor++;
}

void zeraPeso(Peso *peso)
{
	for (int i = 0; i < peso->nValor; i++)
		peso->valor[i] = '\0';
	peso->nValor = 0;
}

// Vertice
Vertice *criaVertice(int id)
{
	Vertice *vertice = new Vertice;
	vertice->id = id;
	vertice->nome = "";
	vertice->aresta = (Aresta **)malloc(MAX_GRAPH_SIZE * sizeof(Aresta *));
	vertice->nArestas = 0;
	cout << "Vertice: " << id << " criado" << endl;
	return vertice;
}

void excluiVertice(Vertice *vertice)
{
	for (int i = 0; i < vertice->nArestas; i++)
		free(vertice->aresta[i]);

	free(vertice);
}

Vertice *encontraVertice(Grafo *grafo, int id)
{
	for (int i = 0; i < grafo->tamanho; i++)
		if (grafo->vertice[i]->id == id)
			return grafo->vertice[i];

	cout << "Vertice: " << id << " nao encontrado" << endl;
	return NULL;
}

Vertice *encontraOuCriaVertice(Grafo *grafo, int id)
{
	Vertice *vertice = encontraVertice(grafo, id);
	if (vertice == NULL)
		vertice = criaVertice(id);
	return vertice;
}

Vertice *encontraVerticePorNome(Grafo *grafo, string nome)
{
	for (int i = 0; i < grafo->tamanho; i++)
		if (grafo->vertice[i]->nome == nome)
			return grafo->vertice[i];

	cout << "\nVertice: " << nome << " nao encontrado" << endl;
	return NULL;
}

void insereVertice(Grafo *grafo, int linha, string pesos, string vertice)
{
	Vertice *inicio = encontraOuCriaVertice(grafo, linha);
	insereGrafo(grafo, inicio);
	inicio->nome = vertice;

	Peso *peso = criaPeso();
	int sobrecarga = 0;
	for (int i = 0; i <= pesos.length(); i++)
	{
		if (pesos[i] == ' ' || pesos[i] == '\0')
		{
			int id = (i - sobrecarga) / 2;
			Vertice *fim = encontraOuCriaVertice(grafo, id);
			insereAresta(inicio, fim, charParaInt(peso->valor));
			insereGrafo(grafo, fim);
			zeraPeso(peso);
		}
		else
		{
			inserePeso(peso, pesos[i]);
			if (peso->nValor >= 2)
				sobrecarga++;
		}
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
	if (origem->id == destino->id || peso <= 0)
		return;

	Aresta *aresta = criaAresta(peso, destino);
	origem->aresta[origem->nArestas] = aresta;
	origem->nArestas++;
	cout << "Aresta adicionada de " << origem->id << " ate " << destino->id << endl;
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
	for (int i = 0; i < grafo->tamanho; i++)
		if (grafo->vertice[i]->id == vertice->id)
			return;

	grafo->vertice[grafo->tamanho] = vertice;
	grafo->tamanho++;
	cout << "Vertice: " << vertice->id << " adicionado ao grafo | " << grafo->tamanho << endl;
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
int charParaInt(char *c)
{
	return atoi(c);
}

// Servicos
void encontraMenorCaminho(Grafo *grafo, string inicio, string fim)
{
	Vertice *origem = encontraVerticePorNome(grafo, inicio);
	Vertice *destino = encontraVerticePorNome(grafo, fim);

	if (origem != NULL && destino != NULL)
		if (origem->id == destino->id)
			cout << "\nVoce ja esta no vertice desejado.\n";
		else
		{
			Fila *fila = criaFila();
			Historico *historico = criaHistorico(origem, destino);
			insereFilaHistorico(historico, fila);
			percorreFila(fila, origem, 0, historico);

			Fila *melhor = melhorFila(historico);

			if (melhor != NULL)
			{
				cout << "\n          ### Distância Total: " << melhor->peso << "km ###\n";
				melhor->peso;
				for (int i = 0; i < melhor->nRotas; i++)
				{
					Rota *rota = melhor->rota[i];
					cout << "-- Percorra " << rota->peso << "km de " << rota->de->nome << " até " << rota->para->nome << endl;
				}
			}
			else
				cout << "\nNenhum caminho valido foi encontrado;\n";

			excluiHistorico(historico);
		}
}

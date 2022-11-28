#include <stdio.h>
#include <stdlib.h>


void limpar_tela() {
    //system("cls");
    //printf("\033[2J"); /* limpa a tela */
    //printf("\033[1H"); /* põe o cursor no topo */
}

typedef struct Nodo {
    int peso, destino;
    Nodo *proximo;
} Nodo;

typedef struct Grafo {
    int maximo_vertices, maximo_arestas_por_vertice, orientado;
    Nodo **adjacencias;
} Grafo;

Nodo *Nodo_novo(int destino, int peso, Nodo *proximo) {
    Nodo *a = (Nodo*)malloc(sizeof(Nodo));
    a->peso = peso;
    a->destino = destino;
    a->proximo = proximo;
    return a;
}

void Nodo_destroi(Nodo *nodo) {
    Nodo *atual = nodo;
    while (atual != NULL) {
        Nodo *aux = atual->proximo;
        free(atual);
        atual = aux;
    } 
}

Grafo *Grafo_novo(int orientado, int maximo_vertices, int maximo_arestas_por_vertice) {
    int x;
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    g->orientado = orientado;
    g->maximo_vertices = maximo_vertices;
    g->maximo_arestas_por_vertice = maximo_arestas_por_vertice;
    g->adjacencias = (Nodo**)malloc(maximo_vertices * sizeof(Nodo *));
    for (x = 0; x < maximo_vertices; x++) {
        g->adjacencias[x] = NULL;
    }
    return g;
}

void Grafo_destroi(Grafo *g) {
    int x;
    for (x = 0; x < g->maximo_vertices; x++) {
        Nodo_destroi(g->adjacencias[x]);
    }
    free(g->adjacencias);
    free(g);
}

void Grafo_inserir_aresta(Grafo *g, int origem, int destino, int peso) {
    Nodo *a;
    int qtda = 0;

    if (origem == destino) {
        printf("Nao e possivel adicionar laço\n");
        return;
    }

    if (destino > g->maximo_vertices) {
        printf("Nao e possivel adicionar, este vertice nao existe.\n");
        return;
    }

    for (a = g->adjacencias[origem]; a != NULL; a = a->proximo) {
        qtda++;

        if (a->peso == destino) {
            printf("Nao sera possivel adicionar aresta paralela.\n");
            return;
        }
    }

    if (qtda > g->maximo_arestas_por_vertice) {
        printf("Nao e possivel adicionar mais arestas ao vertice %d.\n", origem);
        return;
    }

    g->adjacencias[origem] = Nodo_novo(destino, peso, g->adjacencias[origem]);
    if (g->orientado) g->adjacencias[destino] = Nodo_novo(origem, peso, g->adjacencias[destino]);
}

void Grafo_imprime(Grafo *g) {
    Nodo *a;
    int i;

    for (i = 0; i < g->maximo_vertices; i++) {
        printf("|%d|-", i);

        for (a = g->adjacencias[i]; a != NULL; a = a->proximo) {
            printf("[%d,p%d]%s", a->destino, a->peso);
        }

        printf("0\n");
    }

    printf("\n");
}

int main() {

}
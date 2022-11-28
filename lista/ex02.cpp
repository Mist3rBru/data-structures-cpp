#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>

/* 2. Implemente uma função que tenha como valor de retorno o comprimento de uma lista encadeada, 
      isto é, calcule o número de nós da lista. Esta função deve obedecer ao protótipo:
	  int comprimento (lista* l); */

//Declaração da struct Node
struct Node{
	int num;
	struct Node *prox;
}; 
typedef struct Node lista;


int tam;

void inicia(lista *LISTA);
void insereInicio(lista *LISTA);
void libera(lista *LISTA);
int comprimento(lista *l);

//==============================================================================
int main(void)
{	
	system("cls");
    
    lista *LISTA = (lista*)malloc(sizeof(lista));
   
    inicia(LISTA);
	
	//efetua a leitura de valores
	insereInicio(LISTA);
	insereInicio(LISTA);
	insereInicio(LISTA);
	insereInicio(LISTA);
	insereInicio(LISTA);
	
	tam = comprimento(LISTA);
	
	printf("O tamanho da lista eh %d",tam);
	 
    libera(LISTA);
    
    getch(); //Aguarda comando para sair do programa
}

int comprimento(lista *l)
{
	int contador=0;
	lista *p;
	
	p = l;
	
	if (l == NULL)
		return 0;
	else
		while(p->prox != NULL)
		{
			contador++;
			p = p->prox;
		}
		
	return contador;
}


//==============================================================================
void inicia(lista *LISTA)
{
	LISTA->prox = NULL;
}

//==============================================================================
lista *aloca()
{
	lista *novo=(lista *) malloc(sizeof(lista));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
		printf("Novo elemento: "); scanf("%d", &novo->num);
		return novo;
	}
}

//==============================================================================
void insereInicio(lista *LISTA)
{
	lista *novo=aloca();	
	lista *oldHead = LISTA->prox;
	
	LISTA->prox = novo;
	novo->prox = oldHead;
	
	tam++;
}

//==============================================================================
void libera(lista *LISTA)
{
	if(LISTA != NULL ){
		lista *proxNode,
			  *atual;
		
		atual = LISTA->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}


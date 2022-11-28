#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>


/* 7. Escreva um algoritmo que forneça o maior elemento, o menor elemento, 
   e a média aritmética dos elementos de uma lista simplesmente encadeada.

*/

//==============================================================================   
struct lista {
	int valor;
	struct lista* prox;
};

typedef struct lista Lista;
//==============================================================================
Lista* inicializa (void);
Lista* insere (Lista* l, int valor);
void imprime (Lista* l);
void libera (Lista* l);
int maiorElemento(Lista* l);
int menorElemento(Lista* l);
float mediaElemento(Lista* l);

//==============================================================================
int main()
{
	
	system("cls");
    
    Lista *listaValores;
	Lista *tmp;
	 
	//Inicializa a lista;
	listaValores = inicializa();
		
	listaValores = insere(listaValores, 1);
	listaValores = insere(listaValores, 2);
	listaValores = insere(listaValores, 3);
	listaValores = insere(listaValores, 4);
	listaValores = insere(listaValores, 5);
	listaValores = insere(listaValores, 2);
	
	//Imprime toda a lista
    printf ("\n\nLista original....\n");
	imprime(listaValores);
	
	//Maior valor
	printf ("\n\nO maior valor da lista eh: %d\n",maiorElemento(listaValores));
	
	//Menor valor
	printf ("\n\nO menor valor da lista eh: %d\n",menorElemento(listaValores));
	
	//Media
	printf ("\n\nA media de valores da lista eh: %.2f\n",mediaElemento(listaValores));
	
	//Limpa a lista
	libera(listaValores);
        
    printf ("\n\n\n\nPressione qualquer tecla para finalizar o programa.....");    
    getch(); //Aguarda comando para sair do programa
}

//==============================================================================
void imprime (Lista* l)
{
	Lista* p;	 /* vari?vel auxiliar para percorrer a lista */
	for (p = l; p != NULL; p = p->prox)
		printf("info = %d\n", p->valor);
}
//==============================================================================
Lista* insere (Lista* l, int valor)
{
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->valor = valor;
	novo->prox = l;
	return novo;
}
//==============================================================================
Lista* inicializa (void)
{
	return NULL;
}
//============================================================================== 
void libera (Lista* l)
{
	Lista* p = l;
	while (p != NULL) 
	{
		Lista* t = p->prox; /* guarda refer?ncia para o pr?ximo elemento */
		free(p); 	/* libera a mem?ria apontada por p */
		p = t; 	/* faz p apontar para o pr?ximo */
	}
}
//==============================================================================
int maiorElemento(Lista* l)
{
	int maior=0;
	Lista* p = l;
	
	if (l != NULL)
		maior = l->valor;
	
	while (p != NULL) 
	{
		if (maior < p->valor)
			maior = p->valor;
			
		p = p->prox; 
	}
	return maior;	
}

//==============================================================================
int menorElemento(Lista* l)
{
	int menor=0;
	Lista* p = l;
	
	if (l != NULL)
		menor = l->valor;
	
	while (p != NULL) 
	{
		if (menor > p->valor)
			menor = p->valor;
			
		p = p->prox; 
	}
	return menor;
	
}

//==============================================================================
float mediaElemento(Lista* l)
{
	float media=0;
	int cont=0;
	Lista* p = l;

	while (p != NULL) 
	{
		media = media + p->valor;
		cont++;	
		p = p->prox; 
	}
	return (media / cont);
}



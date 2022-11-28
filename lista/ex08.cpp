#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>


/* 8. Duas listas com valores int, não ordenados, simplesmente encadeados, 
	solicite para o usuário informar o numero de elementos das listas para que possa ser 
	utilizado para saber quantos elementos devem ser lidos pelo usuário.  
	Apresente um programa que intercale as duas listas, 
	de forma que a lista resultante contenha todos os elementos das duas listas.

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
Lista* lerValores (Lista* l, char *nomelista, int qtdItens);
Lista* intercalaLista (Lista* l1, Lista* l2);

//==============================================================================
int main()
{
	
	system("cls");
    
    Lista *listaValores, *listaValores2;
    int qtdlista1, qtdlista2;
	 
	//Inicializa a lista;
	listaValores = inicializa();
	listaValores2 = inicializa();
	
	//le a quantidade de elementos
    printf("Informe a quantidade de elementos da lista 1:\n");
    fflush(stdin);
    scanf("%d",&qtdlista1);
    printf("Informe a quantidade de elementos da lista 1:\n");
    fflush(stdin);
    scanf("%d",&qtdlista2);
	
	//le os valores da lista
	listaValores = lerValores(listaValores,"Lista 1", qtdlista1);
	listaValores2 = lerValores(listaValores2,"Lista 2", qtdlista2);
	
	//Intervala as listas
	listaValores = intercalaLista(listaValores, listaValores2);
	
	//Imprime toda a lista
    printf ("\n\nLista intercalada....\n");
	imprime(listaValores);

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
//================================================================================
Lista* lerValores (Lista* l, char *nomelista, int qtdItens)
{
	int valor;
	for(int i = 0; i < qtdItens; i++){
		printf("Insira o elemento [%d] da lista [%s]: ",i,nomelista);
		scanf("%d",&valor);
		l = insere(l, valor);
	}
	return l;
}
//===================================================================================
Lista* intercalaLista (Lista* l1, Lista* l2)
{
	Lista* tmp;
	//avanca ate o final da primeira lista
	tmp = l1;
	while(tmp != NULL)
	{
		if (tmp->prox == NULL)
		{
			tmp->prox = l2;
			return l1;
		}
		tmp = tmp->prox;
	}
}


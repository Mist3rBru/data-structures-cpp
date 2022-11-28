#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>


/* 5. Implemente uma função que tenha como valor de retorno um ponteiro para o último n de uma 
     lista encadeada que contém um determinado valor inteiro x. 
	 Imprima o último elemento. Essa função deve obedecer ao protótipo:
	Lista2* ultimo_x (Lista2* l, int x);
*/

//==============================================================================   
struct lista {
	int valor;
	struct lista* prox;
};

typedef struct lista Lista2;
//==============================================================================
Lista2* inicializa (void);
Lista2* insere (Lista2* l, int valor);
void imprime (Lista2* l);
void libera (Lista2* l);
Lista2* ultimo_x (Lista2* l, int x);

//==============================================================================
int main()
{
	
	system("cls");
    
    Lista2 *listaValores;
	Lista2 *tmp;
	 
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
	
	//Altera caracter
    printf ("\n\nLocalizando o valor....");	
    tmp = ultimo_x(listaValores, 2);//troca o caracter B pelo W	
	
    printf ("\n\nLista com o elemento encontrado....\n");
	imprime(tmp);
	
	//Limpa a lista
	libera(listaValores);
        
    printf ("\n\n\n\nPressione qualquer tecla para finalizar o programa.....");    
    getch(); //Aguarda comando para sair do programa
}

//==============================================================================
void imprime (Lista2* l)
{
	Lista2* p;	 /* vari?vel auxiliar para percorrer a lista */
	for (p = l; p != NULL; p = p->prox)
		printf("info = %d\n", p->valor);
}
//==============================================================================
Lista2* insere (Lista2* l, int valor)
{
	Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
	novo->valor = valor;
	novo->prox = l;
	return novo;
}
//==============================================================================
Lista2* inicializa (void)
{
	return NULL;
}
//============================================================================== 
void libera (Lista2* l)
{
	Lista2* p = l;
	while (p != NULL) 
	{
		Lista2* t = p->prox; /* guarda refer?ncia para o pr?ximo elemento */
		free(p); 	/* libera a mem?ria apontada por p */
		p = t; 	/* faz p apontar para o pr?ximo */
	}
}
//==============================================================================
Lista2* ultimo_x (Lista2* l, int x)
{
          
	Lista2* p;
	Lista2* posElem = NULL;
	
	for (p=l; p!=NULL; p=p->prox)
	{
		if (p->valor == x)
		{
			posElem = p;   
        }
    } 
    
    return posElem;
}
//==============================================================================



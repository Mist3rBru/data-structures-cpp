#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>


/* 6. Implemente uma função que receba como parâmetro uma lista encadeada e um valor inteiro n, 
      e retire da lista todas as ocorrências de n, e retorne a lista resultante. 
	  Imprima a lista atualizada. Essa função deve obedecer ao protótipo:
		Lista* retira_n (Lista* l, int n);

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
Lista* retira_n (Lista* l, int n);

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
	
	//Altera caracter
    printf ("\n\nLocalizando o valor e removendo....");	
    tmp = retira_n(listaValores, 2);
	
    printf ("\n\nLista com o elemento encontrado....\n");
	imprime(tmp);
	
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
Lista* retira_n (Lista* l, int n)
{
	Lista* p;
	Lista* posElem = NULL;
	
	p = l;
	while(p != NULL)
	{
		if (p->valor == n)
		{
			if (posElem == NULL)
				l = p->prox;
			else
			{
				posElem->prox = p->prox;
			}
        }
		posElem = p;
        p=p->prox;
	}
    return l;
}
//==============================================================================



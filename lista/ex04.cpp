#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>


/* 4. Implemente uma função que receba como parâmetros uma lista encadeada e dois caracteres (original e novo) e troque todas as 
   ocorrências do caractere original pelo caractere novo. 
   Essa função deve obedecer ao protótipo:	void troca (Lista2* l, char original, char novo); */
   
//==============================================================================   
struct lista {
	char caractere;
	struct lista* prox;
};

typedef struct lista Lista2;
//==============================================================================
Lista2* inicializa (void);
Lista2* insere (Lista2* l, char valor);
void imprime (Lista2* l);
void libera (Lista2* l);
void troca (Lista2* l, char original, char novo);

//==============================================================================
int main()
{
	
	system("cls");
    
    Lista2 *listaCaracteres;
	Lista2 *tmp;
	 
	//Inicializa a lista;
	listaCaracteres = inicializa();
		
	//Insere 5 caracteres
	listaCaracteres = insere(listaCaracteres, 'A');
	listaCaracteres = insere(listaCaracteres, 'B');
	listaCaracteres = insere(listaCaracteres, 'C');
	listaCaracteres = insere(listaCaracteres, 'D');
	listaCaracteres = insere(listaCaracteres, 'E');
	listaCaracteres = insere(listaCaracteres, 'B');
	
	//Imprime toda a lista
    printf ("\n\nLista original....\n");
	imprime(listaCaracteres);
	
	//Altera caracter
    printf ("\n\nTrocando caracter B pelo W....");	
    troca (listaCaracteres, 'B', 'W');//troca o caracter B pelo W	
	
    printf ("\n\nNova lista....\n");
	imprime(listaCaracteres);
	
	//Limpa a lista
	libera(listaCaracteres);
        
    printf ("\n\n\n\nPressione qualquer tecla para finalizar o programa.....");    
    getch(); //Aguarda comando para sair do programa
}

//==============================================================================
void imprime (Lista2* l)
{
	Lista2* p;	 /* vari?vel auxiliar para percorrer a lista */
	for (p = l; p != NULL; p = p->prox)
		printf("info = %c\n", p->caractere);
}
//==============================================================================
Lista2* insere (Lista2* l, char valor)
{
	Lista2* novo = (Lista2*) malloc(sizeof(Lista2));
	novo->caractere = valor;
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
void troca (Lista2* l, char original, char novo)
{
          
	Lista2* p;
	for (p=l; p!=NULL; p=p->prox)
	{
		if (p->caractere == original)
		{
			p->caractere = novo;
            printf ("\n\nCaracter alterado....\n");    
        }
    } 
}
//==============================================================================



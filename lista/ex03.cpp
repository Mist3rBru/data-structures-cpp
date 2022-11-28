#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>

/* 3. Escreva um algoritmo que inverta a ordem dos elementos de uma lista simplesmente encadeada. 
   A invers„o deve ser realizada de forma a n„o alterar a ordem fÌsica dos elementos na lista. */

struct lista{
  int info;
  struct lista* prox;
};

typedef struct lista Lista;

//==============================================================================
Lista* inicializa()
{
   return NULL;
}
//==============================================================================
Lista* insere(Lista* l, int i)
{
   Lista* novo= (Lista*)malloc(sizeof(Lista));
   novo->info = i;
   novo->prox = l;
   return novo;
}
//==============================================================================
Lista* insere(Lista* l, Lista* nodo)
{
   nodo->prox = l;
   return nodo;
}
//==============================================================================
void imprime(Lista* l)
{
   Lista* p;
   for(p=l;p !=NULL;p=p->prox){
     printf("info = %d\n",p->info);
   }
}
//==============================================================================
void libera(Lista* l)
{
   Lista* p = l;
   while (p != NULL){
     Lista* t = p-> prox;
     free(p);
     p = t;
   }
}
//==============================================================================
Lista* inverte(Lista* base) {
	
  Lista* novabase = NULL;
  
  while (base) {
    Lista* proximo = base->prox;
    base->prox = novabase;
    novabase = base;
    base = proximo;
  }
  return novabase;
}

//==============================================================================
int main()
{

	system("cls");
        
    Lista* l; /* declara uma lista n√£o iniciada */
    l = inicializa(); /* inicia lista vazia */
    l = insere(l, 12); /* insere na lista o elemento 23 */
    l = insere(l, 5); /* insere na lista o elemento 45 */
    l = insere(l, 8); /* insere na lista o elemento 56 */
    l = insere(l, 130); /* insere na lista o elemento 78 */
    printf("\nLista iriginal: \n");
    imprime(l);
    printf("\n\nLista invertida: \n"); 
    l = inverte(l);
    imprime(l);   
    
    printf ("\n\n\n\nPressione qualquer tecla para finalizar o programa.....");    
    getch(); //Aguarda comando para sair do programa    
    libera(l);
}

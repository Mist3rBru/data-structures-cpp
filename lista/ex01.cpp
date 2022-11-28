#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>

/*1. Crie um programa "lse.cpp" contendo as seguintes funções:
a)	Inserção no início;
b)	Inserção no final;
c)	Remoção de um elemento v passado como parâmetro;
d)	Busca de um elemento v;
e)	Listagem dos elementos contidos na lista;
f)	Liberar a memória alocada. */

//Declaração da struct Node
struct Node{
	int num;
	struct Node *prox;
}; 
typedef struct Node node;


int tam;

void inicia(node *LISTA);
int menu(void);
void opcao(node *LISTA, int op);
void insereFim(node *LISTA);
void insereInicio(node *LISTA);
void exibe(node *LISTA);
void libera(node *LISTA);
void insere (node *LISTA);
node *retira(node *LISTA);
node* buscaElemento(node *LISTA, int opt);

//==============================================================================
int main(void)
{	
	system("cls");
    
    node *LISTA = (node *) malloc(sizeof(node));
	if(!LISTA){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
    else
    {
    	inicia(LISTA);
    	int opt;
    	
    	do{
    		opt=menu();
    		opcao(LISTA,opt);
    	}while(opt);
    
    
    	free(LISTA); //libera memoria (criar função)
    
        printf ("\n\n\n\nPressione qualquer tecla para finalizar o programa.....");    
        getch(); //Aguarda comando para sair do programa
	}
}
//==============================================================================
void inicia(node *LISTA)
{
	LISTA->prox = NULL;
	tam=0;
}
//==============================================================================
int menu(void)
{
	int opt;
    system("cls"); //Limpa tela....	
	printf("Escolha a opcao\n");
    printf("0. Sair\n");
	printf("1. Adiciona no inicio\n");
	printf("2. Adiciona no final\n");
	printf("3. Retira Elemento\n");
	printf("4. Busca Elemento\n");
	printf("5. Exibir Lista\n");
	printf("6. Libera Memoria\n\n");
	printf("Opcao: "); scanf("%d", &opt);        	
	return opt;
}
//==============================================================================
void opcao(node *LISTA, int op)
{
	node *tmp;
	int opt;
	
	switch(op){
		case 0:
			libera(LISTA); //libera memoria e sai do programa
			break;
			
		case 1:
            insereInicio(LISTA); //adiciona elemento no inicio da lista
            getch(); //Aguarda comando...
			break;
		
		case 2:
			insereFim(LISTA); //adiciona elemento no final da lista
            getch(); //Aguarda comando...			
			break;
		
		case 3:
			retira(LISTA);
			break;		
			
		case 4:
			
            printf("\nQual elemento voce deseja encontrar: ");
	        scanf("%d", &opt);
            tmp = buscaElemento(LISTA,opt);
        	if (tmp != NULL)
        		printf("O valor foi encontrado: %d\n", tmp->num);
        	else
        		printf("Valor nao encontrado na lista....\n");    
            getch(); //Aguarda comando para sair do programa 
			break;
			
		case 5:
			exibe(LISTA);
			break;
		
		case 6:
			libera(LISTA); //libera memoria
			printf("Memoria liberada....\n");
			getch(); //Aguarda comando para sair do programa 
			break;
		
		default:
			printf("Comando invalido....\n\n");
			getch(); //Aguarda comando para sair do programa 
	}
}
//==============================================================================
int vazia(node *LISTA)
{
	if(LISTA->prox == NULL)
		return 1;
	else
		return 0;
}
//==============================================================================
node *aloca()
{
	node *novo=(node *) malloc(sizeof(node));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
		printf("Novo elemento: "); scanf("%d", &novo->num);
		return novo;
	}
}
//==============================================================================

void insereFim(node *LISTA)
{
	node *novo=aloca();
	novo->prox = NULL;
	
	if(vazia(LISTA))
		LISTA->prox=novo;
	else{
		node *tmp = LISTA->prox;
		
		while(tmp->prox != NULL)
			tmp = tmp->prox;
		
		tmp->prox = novo;
	}
	tam++;
}
//==============================================================================
void insereInicio(node *LISTA)
{
	node *novo=aloca();	
	node *oldHead = LISTA->prox;
	
	LISTA->prox = novo;
	novo->prox = oldHead;
	
	tam++;
}
//==============================================================================
void exibe(node *LISTA)
{
	if(vazia(LISTA)){
		printf("Lista vazia!\n\n");
        getch(); //Aguarda comando...
		return ;
	}
	
	node *tmp;
	tmp = LISTA->prox;
	printf("Lista:");
	while( tmp != NULL){
		printf("%5d", tmp->num);
		tmp = tmp->prox;
	}
	printf("\n        ");
	int count;
	for(count=0 ; count < tam ; count++)
		printf("  ^  ");
	printf("\nOrdem:");
	for(count=0 ; count < tam ; count++)
		printf("%5d", count+1);
	
		
	printf("\n\n");
    getch(); //Aguarda comando para sair do programa
}
//==============================================================================
void libera(node *LISTA)
{
	if(!vazia(LISTA)){
		node *proxNode,
			  *atual;
		
		atual = LISTA->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}
//==============================================================================
void insere(node *LISTA)
{
	int pos,
		count;
	printf("Em que posicao, [de 1 ate %d] voce deseja inserir: ", tam);
	scanf("%d", &pos);
	
	if(pos>0 && pos <= tam)
    {
		if(pos==1)
			insereInicio(LISTA);
		else{
			node *atual = LISTA->prox,
				 *anterior=LISTA; 
			node *novo=aloca();
				 
			for(count=1 ; count < pos ; count++){
					anterior=atual;
					atual=atual->prox;
			}
			anterior->prox=novo;
			novo->prox = atual;
			tam++;
		}
			
	}
    else
	{
		printf("Elemento invalido\n\n");
    }    
        
   getch(); //Aguarda comando para sair do programa     		
}
//==============================================================================
node *retira(node *LISTA)
{
	int opt,
		count;
	printf("Qual elemento voce deseja retirar: ");
	scanf("%d", &opt);
	
    node* ant = NULL; /* ponteiro para elemento anterior */
    node* p = LISTA; /* ponteiro para percorrer a lista*/
	
       while (p != NULL && p->num != opt) 
       {
             ant = p;
             p = p->prox;
       }    
    
    /* verifica se achou elemento */
    if (p == NULL)
    {
     printf("Elemento invalido\n\n");
     return LISTA; /* n?o achou: retorna lista original */    
    }
    
    if (ant == NULL) 
    {
              /* retira elemento do inicio */
              LISTA = p->prox;
              tam--;
    }
    else 
    {
              /* retira elemento do meio da lista */
              ant->prox = p->prox;
              tam--;
    }
    free(p); 
    printf("Elemento removido\n\n"); 
    getch(); //Aguarda comando para sair do programa       
       	
}

//==============================================================================
node* buscaElemento(node *LISTA, int opt)
{
    
    //int opt;
    
	//printf("Qual elemento voce deseja encontrar: ");
	//scanf("%d", &opt);
		
	node* p;
	for (p=LISTA; p!=NULL; p=p->prox)
	{
		if (p->num == opt)
			return p;
    }
	return NULL; //nao encontrou   
    
      
       	
}
//==============================================================================

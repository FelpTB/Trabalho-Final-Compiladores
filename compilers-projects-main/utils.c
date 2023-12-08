// Tabela de Simbolos
#include <stdio.h>
#include <stdlib.h>

typedef struct no *ptno;

typedef struct listaCampos{
    char nome[100];
    int tip;
    int posicao;
    int deslocamento;
    int tamanho;
}listaCampos;

struct no{
	char info;
	ptno prox;
};

ptno insere(ptno L,char info){

	ptno p, new;
	new = (ptno) malloc (sizeof(struct no));
	new -> info = info;
	new -> prox = NULL;
	p=L;
	while(p && p->prox){
		p=p->prox;
		if(p){
			p->prox=new;
		}else{
			L = new;
		}
	}
	return L;
}



ptno busca(ptno L, char info){
	while(L && L->info!=info){
		L=L->prox;
	}
	return L;
}

void mostra(ptno L){
    printf("[");
    while(L){
        if(L->prox){
            printf("%c", L->info);
        }else{
            printf("%c", L->info);
        
        }
        L=L->prox;
    }
    printf("]\n");
}



enum 
{
    INT,
    LOG,
    REG
};

char nomeTipo[3][4]={"INT","LOG","REG"};


#define TAM_TAB 100
//acrescentar a lista de campos

struct elemTabSimbolos {
    char id[100]; // nome do identificador
    int end;     //endereço
    int tip;    //tipo
    int tam;	//tamanho
    int posição; //posição
    listaCampos* listaDeCampos;	//lista de campo
} tabSimb[TAM_TAB], elemTab;

int posTab = 0; // indica a proxima posição livre para inserir

int buscaSimbolo (char *s) {
    int i;
    for(i = posTab - 1; strcmp(tabSimb[i].id, s) && i >= 0; i--);
    if ( i == -1) {
        char msg[200];
        sprintf(msg, "Identificador [%s] não encontrado!", s);
        yyerror (msg);
    }
    return i; 

}

void insereSimbolo (struct elemTabSimbolos elem) {
    int i;
    if(posTab == TAM_TAB)
        yyerror ("Tabela de Simbolos cheia!");
    for(i = posTab - 1; strcmp(tabSimb[i].id, elem.id) && i >= 0; i--)
        ;
    if(i != -1){
        char msg[200];
        sprintf(msg, "Identificador [%s] duplicado", elem.id);
        yyerror (msg);
    }
    tabSimb[posTab++] = elem;
}

void mostraTabela (){
    printf("%55s","TabelaDeSimbolos\n");
    puts("----------------------------------------------------------------------------------------------------\n");
    printf("%30s | %s | %s | %s | %s | %s |\n","ID", "END", "TIPO", "TAM", "POS", "CAMPOS");
    for (int i = 0; i < 50; i++)
        printf("--");
    for (int i = 0; i < posTab; i++)
        printf("\n%30s | %3d | %d | %d | %d | (%s,%3d,%d,%d,%d)=> %s |",
            tabSimb[i].id,
            tabSimb[i].end,
            tabSimb[i].tip,
            tabSimb[i].tam,
            tabSimb[i].posição,
            tabSimb[i].listaDeCampos->nome,
            tabSimb[i].listaDeCampos->tip,
            tabSimb[i].listaDeCampos->tamanho,
            tabSimb[i].listaDeCampos->posicao,
            tabSimb[i].listaDeCampos->deslocamento,
            nomeTipo[tabSimb[i].tip]);
    puts(" ");
}

// Pilha Semantica
#define TAM_PIL 100
int pilha[TAM_PIL];
int topo = -1;

void empilha (int valor) {
    if(topo == TAM_PIL)
        yyerror("Pilha semantica cheia!");
    pilha[++topo] = valor;
}

int desempilha (void) {
    if(topo == -1)
        yyerror("Pilha semantica vazia!");
    return pilha[topo--];
}

// tipo1 e tipo2 são os tipos esperados na expressão
// ret é o tipo que será empilhado com resultado da expressão
void testaTipo (int tipo1, int tipo2, int ret) {
    int t1 = desempilha();
    int t2 = desempilha();
    if (t1 != tipo1 || t2 != tipo2) 
        yyerror("Incompatibilidade de tipo!");
    empilha(ret);
}

// typedef struct no *ptno;

// struct no{
// 	char info;
// 	ptno prox;
//     int tam;
//     int pos;
//     int des;
    
// };

// ptno insere(ptno L,char info){

// 	ptno p, new;
// 	new = (ptno) malloc (sizeof(struct no));
// 	new -> info = info;
// 	new -> prox = NULL;
// 	p=L;
// 	while(p && p->prox){
// 		p=p->prox;
// 		if(p){
// 			p->prox=new;
// 		}else{
// 			L = new;
// 		}
// 	}
// 	return L;
// }

// ptno busca(ptno L, char info){
// 	while(L && L->info!=info){
// 		L=L->prox;
// 	}
// 	return L;
// }

// void mostra(ptno L){
//     printf("[");
//     while(L){
//         if(L->prox){
//             printf("%c", L->info);
//         }else{
//             printf("%c", L->info);
        
//         }
//         L=L->prox;
//     }
//     printf("]\n");
// }
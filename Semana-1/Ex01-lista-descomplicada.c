/*1. Crie um programa que:
(a) Aloque dinamicamente um array de 5 números inteiros,
(b) Peca para o usuario digitar os 5 numeros no espaco alocado,
(c) Mostre na tela os 5 numeros,
(d) Libere a memória alocada.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    int num;
    struct cel *prox;
}celula;

celula *cria_lista()
{
    celula *head = ( celula * )malloc( sizeof( celula ) );
    head->prox = NULL;
    return head;
}

void insere_no_fim( int num, celula *lista )
{
    celula *fim, *nova = ( celula * )malloc( sizeof( celula ) );
    for( fim = lista; fim->prox != NULL; fim = fim->prox);
    nova->num = num;
    nova->prox = fim->prox;
    fim->prox = nova;
}

void imprime( celula *lista )
{
    celula *p;
    for( p = lista->prox; p != NULL; p = p->prox )
    printf( "%d ", p->num );
}

celula *apagaLista( celula *lista )
{
    celula *p = lista, *temp = NULL;
    while (p != NULL){
        temp = p->prox;
        free(p);
        p = temp;
    }
    return NULL;
}

int main()
{
    int num, i;
    celula *lista = cria_lista();
    printf( "Digite 5 numeros inteiros:\n" );
    for( i = 0; i < 5; i++ ){
        scanf( "%d", &num );
        insere_no_fim( num, lista );
    }
    imprime( lista );
    lista = apagaLista( lista );
    return 0;
}
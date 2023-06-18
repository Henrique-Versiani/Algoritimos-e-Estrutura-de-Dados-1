/*5. Faca um programa que leia um numero N e:
• Crie dinamicamente e leia um vetor de inteiro de N posicoes;
• Leia um numero inteiro X e conte e mostre os multiplos desse numero que existem
no vetor.
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

void multiplo( celula *lista )
{
    celula *p, *q;
    for( p = lista->prox; p != NULL; p = p->prox ){
        for( q = lista->prox; q != NULL; q = q->prox ){
            if( q->num % p->num == 0 )
                printf( "\n%d eh multiplo de %d", q->num, p->num );
        }
        printf( "\n" );
    }

}

celula *apagaLista(celula *lista)
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
    celula *lista = cria_lista();
    int i, N, num;

    printf( "Digite um valor N: " );
    scanf( "%d", &N );

    for( i = 0; i < N; i++ ){
        printf( "\nDigite um numero inteiro: " );
        scanf( "%d", &num );
        insere_no_fim( num, lista );
    }
    multiplo( lista );
    lista = apagaLista( lista );
    return 0;
}
/*20. Faca um programa que:
(a) Peca para o usuario entrar com o nome e a posicao (coordenadas X e Y) de N 
cidades e as armazene em um vetor de estruturas (N e informado pelo usuario); 
(b) Crie uma matriz de distancias entre cidades de tamanho N x N;
(c) Calcule as distancia entre cada duas cidades e armazene na matriz;
(d) Exiba na tela a matriz de distancias obtida; 
(e) Quando o usuario digitar o numero de duas cidades o programa devera retornar a
distancia entre elas.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct coordenanda{
    int x;
    int y;
}coord;

typedef struct cel{
    char nome[50];
    coord local;
    struct cel *prox;
}celula;

celula *cria_lista ( void )
{
    celula *head = ( celula * )malloc( sizeof( celula ) );
    head->prox = NULL;
    return head;
}

void insere_no_fim ( char nome[], coord local, celula *lista )
{
    celula *fim, *nova = ( celula * )malloc( sizeof( celula ) );
    for( fim = lista; fim->prox != NULL; fim = fim->prox );
    strcpy ( nova->nome, nome );
    nova->local.x = local.x;
    nova->local.y = local.y;
    nova->prox = fim->prox;
    fim->prox = nova;
}

void imprime ( celula *lista )
{
    celula *p;
    int i = 0;
    for ( p = lista->prox; p != NULL; p = p->prox, i++ ){
        printf ( "\n-------- Cidade %d ---------\n", i );
        printf ( "Nome: %s\n", p->nome );
        printf ( "Local: (%d, %d)\n", p->local.x, p->local.y );
    }   
}

int menu ( void )
{
    int escolha;
    do{
        printf ( "\n--------- MENU ---------\n" );
        printf ( "1: imprime\n2: calcular distancia\n3: Sair\n" );
        scanf  ( "%d", &escolha );
        getchar( );
    }while ( escolha < 1 || escolha > 3 );
    return escolha;
}

celula *apagaLista ( celula *lista )
{
    celula *p = lista, *temp = NULL;
    while ( p != NULL ){
        temp = p->prox;
        free( p );
        p = temp;
    }
    return NULL;
}

float distancia ( int cid_1, int cid_2, celula *lista )
{
    int i = 0;
    celula *p, *q;
    float dist;
    for ( p = lista->prox; p != NULL && i != cid_1; p = p->prox, i++ );
    i = 0;
    for ( q = lista->prox; q != NULL && i != cid_2; q = q->prox, i++ );

    dist = sqrt ( pow ( p->local.x - q->local.x , 2 ) + pow ( p->local.y - q->local.y , 2 ) );
    return dist;
}

int main ( void )
{
    celula *lista = cria_lista( );
    char nome[50];
    coord local;
    int mainmenu, cid1, cid2, N, i;
    float dist;

    printf ( "Digite a quantidade de cidades a serem inseridas: " );
    scanf  ( "%d", &N );
    getchar( );
    for ( i = 0; i < N; i++ ){
        printf ( "\nDigite o nome da cidade: " );
        scanf  ( "%[^\n]s", nome );
        printf ( "\nDigite a coordenada x: " );
        scanf  ( "%d", &local.x );
        printf ( "\nDigite a coordenada y: " );
        scanf  ( "%d", &local.y );
        getchar( );
        insere_no_fim ( nome, local, lista );
    }
    for ( ;; ){
        mainmenu = menu( );
        switch( mainmenu ){
            case 1:
                imprime( lista );
                break;
            case 2:
                printf ( "\nDigite o numero da cidade 1: ");
                scanf  ( "%d", &cid1 );
                printf ( "\nDigite o numero da cidade 2: ");
                scanf  ( "%d", &cid2 );
                dist = distancia( cid1, cid2, lista );
                printf ( "\nA distancia entre as duas cidades eh: %.2f", dist );
                break;
            case 3:
                lista = apagaLista( lista );
                exit ( 0 );
        }
    }
    return 0;
}
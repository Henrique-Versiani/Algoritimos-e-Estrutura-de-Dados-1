/*12. Considere um cadastro de produtos de um estoque, com as seguintes informacoes para
cada produto:
• Codigo de identificacao do produto: representado por um valor inteiro
• Nome do produto: com ate 50 caracteres
• Quantidade disponıvel no estoque: representado por um numero inteiro
• Prec¸o de venda: representado por um valor real
(a) Defina uma estrutura, denominada produto, que tenha os campos apropriados para
guardar as informacoes de um produto
(b) Crie um conjunto de N produtos (N e um valor fornecido pelo usuario) e peca ao
usuario para entrar com as informacoes de cada produto
(c) Encontre o produto com o maior preco de venda
(d) Encontre o produto com a maior quantidade disponıvel no estoque
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cel{
    float preco;
    int estoque, ID;
    char nome[50];
    struct cel *prox;
}produto;

produto *cria_lista ( void )
{
    produto *head = ( produto * )malloc( sizeof( produto ) );
    head->prox = NULL;
    return head;
}

void insere_no_fim ( int ID, char nome[], int estoque, float preco, produto *lista )
{
    produto *fim, *nova = ( produto * )malloc( sizeof( produto ) );
    for ( fim = lista; fim->prox != NULL; fim = fim->prox );
    nova->ID = ID;
    strcpy( nova->nome, nome );
    nova->estoque = estoque;
    nova->preco = preco;
    nova->prox = fim->prox;
    fim->prox = nova;
}

void imprime ( produto *lista )
{
    produto *p;
    int i = 0;
    for ( p = lista->prox; p != NULL; p = p->prox, i++ ){
        printf ( "\n----------- produto %d ------------\n", i);
        printf ( "ID: %d\n", p->ID );
        printf ( "Nome: %s\n", p->nome );
        printf ( "Estoque: %d\n", p->estoque );
        printf ( "Preco: %.2f\n", p->preco );
    }
}

int menu( void )
{
    int escolha;
    do{
        printf ( "\n---------- MENU ----------\n" );
        printf ( "1: Imprime\n" );
        printf ( "2: Produto de maior preco\n" );
        printf ( "3: Produto com maior estoque\n" );
        printf ( "4: sair\n" );
        scanf  ( "%d", &escolha );
        getchar( );
    }while ( escolha < 1 || escolha > 4 );
    return escolha;
}

void maior_preco ( produto *lista )
{
    produto *p;
    int i = 0;
    float maior = 0;
    for ( p = lista->prox; p != NULL; p = p->prox ){
        if ( p->preco > maior )
            maior = p->preco;
    }
    for ( p = lista->prox; p != NULL; p = p->prox, i++ ){
        if ( maior == p->preco ){
            printf ( "\n----------- produto %d ------------\n", i);
            printf ( "ID: %d\n", p->ID );
            printf ( "Nome: %s\n", p->nome );
            printf ( "Estoque: %d\n", p->estoque );
            printf ( "Preco: %.2f\n", p->preco );
        }
    }
}

void maior_estoque ( produto *lista )
{
    produto *p;
    int i = 0;
    int maior = 0;
    for ( p = lista->prox; p != NULL; p = p->prox ){
        if ( p->estoque > maior )
            maior = p->estoque;
    }
    for ( p = lista->prox; p != NULL; p = p->prox, i++ ){
        if ( maior == p->estoque ){
            printf ( "\n----------- produto %d ------------\n", i);
            printf ( "ID: %d\n", p->ID );
            printf ( "Nome: %s\n", p->nome );
            printf ( "Estoque: %d\n", p->estoque );
            printf ( "Preco: %.2f\n", p->preco );
        }
    }
}

produto *apagaLista ( produto *lista )
{
    produto *p = lista, *temp = NULL;
    while ( p != NULL ){
        temp = p->prox;
        free( p );
        p = temp;
    }
    return NULL;
}

int main ( void )
{
    produto *lista = cria_lista ( );
    int mainmenu, ID, estoque, N, i;
    char nome[50];
    float preco;
    
    printf ( "Digite a quantidade de produtos a serem inseridos: ");
    scanf  ( "%d", &N );
    for ( i = 0; i < N; i++ ){
        printf ( "--------- Produto %d ---------", i ); 
        printf ( "\nDigite o ID do produto: " );
        scanf  ( "%d", &ID );
        getchar();
        printf ( "\nDigite o nome do produto: " );
        scanf  ( "%[^\n]s", nome );
        getchar();
        printf ( "\nDigite o estoque do produto: " );
        scanf  ( "%d", &estoque );
        printf ( "\nDigite o preco do produto: " );
        scanf  ( "%f", &preco);
        insere_no_fim ( ID, nome, estoque, preco, lista );
    }
    for ( ;; ){
        mainmenu = menu ( );
        switch ( mainmenu ){
            case 1:
                imprime ( lista );
                break;
            case 2:
                maior_preco ( lista );
                break;
            case 3:
                maior_estoque ( lista );
                break;
            case 4:
                lista = apagaLista ( lista );
                exit ( 0 );
        }
    }
}
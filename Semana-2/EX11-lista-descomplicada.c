/*11. Crie um programa que declare uma estrutura (registro) para o cadastro de alunos.
(a) Deverao ser armazenados, para cada aluno: matrıcula, sobrenome (apenas um) e
ano de nascimento.
(b) Ao inıcio do programa, o usuario devera informar o numero de alunos que serao
armazenados
(c) O programa devera alocar dinamicamente a quantidade necessaria de memoria
para armazenar os registros dos alunos.
(d) O programa devera pedir ao usuario que entre com as informacoes dos alunos.
(e) Ao final, mostrar os dados armazenados e liberar a memoria alocada. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reg {
    int matricula;
    char sobrenome[50];
    int ano;
    struct reg *prox;
}registro;

registro *cria_lista ( void )
{
    registro *head = ( registro * )malloc( sizeof( registro ) );
    head->prox = NULL;
    return head;
}

void insere_no_fim ( int matricula, char sobrenome[], int ano, registro *lista )
{
    registro *fim, *nova = ( registro * )malloc( sizeof( registro ) );
    for ( fim = lista; fim->prox != NULL; fim = fim->prox );
    nova->matricula = matricula;
    strcpy ( nova->sobrenome, sobrenome );
    nova->ano = ano;
    nova->prox = fim->prox;
    fim->prox = nova;
}

void imprime ( registro *lista )
{
    registro *p;
    int i = 0;
    for ( p = lista->prox; p != NULL; p = p->prox, i++ ){
        printf ( "\n--------- Aluno %d ---------\n", i);
        printf ( "Matricula: %d\nSobrenome: %s\nAno de nascimento: %d\n", p->matricula, p->sobrenome, p->ano );
    }
}

registro *apaga_lista ( registro *lista )
{
    registro *p = lista, *temp = NULL;
    while ( p != NULL ){
        temp = p->prox;
        free ( p );
        p = temp;
    }
    return NULL;
}

int main ( void )
{
    registro *lista = cria_lista( );
    int N, i, matricula, ano;
    char sobrenome[50];

    printf ( "informe o numero de alunos: " );
    scanf  ( "%d", &N );

    for ( i = 0; i < N; i++){
        printf ( "\nMatricula do aluno %d: ", i );
        scanf  ( "%d", &matricula );
        getchar();
        printf ( "\nSobrenome do aluno %d: ", i );
        scanf  ( "%[^\n]s", sobrenome );
        printf ( "\nAno de nascimento do aluno %d: ", i );
        scanf  ( "%d", &ano );
        insere_no_fim ( matricula, sobrenome, ano, lista );
    }
    imprime ( lista );
    lista = apaga_lista ( lista );
    return 0;
}
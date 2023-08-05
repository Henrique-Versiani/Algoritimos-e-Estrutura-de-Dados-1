#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 10

typedef struct{
    int idade;
    char nome[50];
}aluno;

typedef struct{
    aluno *alunos[MAX];
    int topo;
    int base;
    int limite;
}pilha;

int menu( void )
{
    int escolha;
    do{
        printf( "\n\t\t----------- MENU -----------");
        printf( "\n\t\t1: adicionar elemento\n\t\t2: remover elemento\n\t\t3: Resetar pilha" );
        printf( "\n\t\t4: Limpar pilha\n\t\t5: Mostrar conteudo da pilha" );
        printf( "\n\t\t6: Sair\n\t\t" );
        scanf( "%d", &escolha );
        getchar( );
    }while( escolha < 1 || escolha > 6 );
    return escolha;
}

void reset ( pilha *pilha )
{
    for( int i = 0; i < MAX; i++ )
        pilha->alunos[i] = NULL;
    pilha->topo = 0;
    pilha->base = 0;
    pilha->limite = MAX;
}

bool empyt( pilha *pilha )
{
    return pilha->topo == 0;
}

bool full( pilha *pilha )
{
    return pilha->topo == MAX;
}

void push( pilha *pilha, aluno *aluno )
{
    if( full( pilha ) )
    {
        printf( "\nA pilha ja esta cheia!!" );
        return;
    }
    pilha->alunos[pilha->topo] = aluno;
    pilha->topo++;
}

void pop( pilha *pilha, aluno *aluno )
{
    if( empyt( pilha ) )
    {
        printf( "\nA pilha ja esta vazia!!" );
        aluno = NULL;
        return;
    }
    pilha->topo--;
    aluno = pilha->alunos[pilha->topo];
}

void clear( pilha *pilha, aluno *aluno )
{
    if( empyt( pilha ) )
    {
        printf( "\nA pilha já esta vazia" );
        return;
    }

    while( !empyt( pilha ) )
    {
        pilha->topo--;
        pop( pilha, aluno );
        free( aluno );
    }
    printf( "\nA pilha agora esta vazia!!" );
}

void listar( pilha *stack )
{
    if ( empyt( stack ) )
    {
        printf( "\nA pilha esta vazia!!" );
        return;
    }
    pilha aux;
    int i = 0;
    reset ( &aux );
    while( !empyt( stack ) )
    {
        stack->topo--;
        printf( "\n-------- Aluno %d --------", i );
        i++;
        printf( "\nIdade: %d\nNome: %s", stack->alunos[stack->topo]->idade, stack->alunos[stack->topo]->nome );
    }
}

int main( void )
{
    int mainmenu, idade;
    char nome[50];
    pilha p;
    reset( &p );

    for ( ; ; )
    {
        mainmenu = menu( );
        switch( mainmenu )
        {
            case 1:
                printf( "\nInforme a idade do aluno: " );
                scanf( "%d", &idade );
                getchar( );
                printf( "\nInforme o nome do aluno: ");
                scanf( "%[^\n]s", nome );
                aluno *pessoa = ( aluno * )malloc( sizeof( aluno ) );
                pessoa->idade = idade;
                strcpy( pessoa->nome, nome );
                push( &p, pessoa );
                break;
            case 2:
                if( !empyt( &p ) ){
                    aluno *pessoa;      
                    pop( &p, &pessoa );
                    free( pessoa );
                    printf("\nEstudante do topo delatado\n");
                }else{
                    printf("\nStack is already empty!\n");
                }
                break;
            case 3:
                reset( &p );
                break;
            case 4:
                if( !empyt( &p ) )
                {
                    aluno *pessoa;
                    clear( &p, &pessoa );
                    free( pessoa );
                }
                break;
            case 5:
                listar( &p );
                break;
            case 6:
                exit( 0 );
        }
    }
}
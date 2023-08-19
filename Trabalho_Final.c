#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
	struct matrix *right;
	struct matrix *below;
	int row;
	int column;
	float info;
}Matrix;

Matrix *matrix_create( void );//-------------------------------->Completo graças a Deus
void matrix_print( Matrix *m );//------------------------------->Completo finalmente
void matrix_setelem( Matrix *m, int x, int y, float elem );//--->Completo
void matrix_destroy( Matrix *m );//----------------------------->Completo
float matrix_getelem( Matrix *m, int x, int y );//-------------->Completo
Matrix* matrix_add( Matrix *m, Matrix *n );//------------------->Faltando
Matrix* matrix_multiply( Matrix *m, Matrix *n );//-------------->Faltando
Matrix* matrix_transpose( Matrix *m );//------------------------>Faltando

int main( void ) {
    float teste;
    printf( "%d", (sizeof(Matrix)));
    Matrix *A = matrix_create();
    teste = matrix_getelem(A, 2, 1);
    printf( "%.2f\n", teste );
    //matrix_print(A);
    matrix_destroy(A);
    return 0;
}

void matrix_setelem( Matrix* m, int x, int y, float elem )
{
    int nRows = 1, nCols = 1;
    Matrix *new = ( Matrix * )malloc( sizeof( Matrix ) );
    new->row = x;
    new->column = y;
    new->info = elem;

    Matrix *p, *q, *r, *s;
    for ( r = m->right; r != m && y != nCols; r = r->right, nCols++ );//-------->Conta a quantidade de Colunas
    for ( s = m->below; s != m && x != nRows; s = s->below, nRows++ );//-------->Conta a quantidade de Linhas

    for ( q = r; q->below != r && q->below->row < x; q = q->below );//---------->Encontra a linha onde a célula será inserida
    for ( p = s; p->right != s && p->right->column < y; p = p->right );//------->Encontra a coluna onde a célula será inserida
    

    new->right = p->right;
    p->right = new;
    new->below = q->below;
    q->below = new;

    if ( ( p->right->right->row == x && p->right->right->column == y ) )//------>Se já houver alguma célula na mesma posição a antiga é desalocada, dando espaço para a nova
    {
        Matrix *temp = p->right->right;
        new->right = temp->right;
        temp->right = NULL;
        new->below = temp->below;
        temp->below = NULL;
        free( temp );
    }
}

Matrix *matrix_create( void ) {
    int i, j, m, n, flag;
    float value;

    printf( "\nEnter the number of rows and columns: " );
    scanf( "%d %d", &m, &n );
    getchar();

    Matrix *head = ( Matrix * )malloc( sizeof( Matrix ) );//------>Cria a cabeça principal

    head->row = -1;
    head->column = -1;
    head->right = NULL;
    head->below = NULL;

    Matrix *head_row[m], *head_col[n];

    for ( i = 0; i < m; i++ )//----------------------------------->Cria a cabeça de cada uma das linhas baseado na entrada 'm'
    {
        head_row[i] = ( Matrix * )malloc( sizeof( Matrix ) );
        head_row[i]->right = head_row[i];//----------------------->Faz a cabeça de cada linha apontar para si própria
        head_row[i]->below = NULL;
        head_row[i]->row = -1;
    }

    for ( i = 0; i < n; i++ )//----------------------------------->Cria a cabeça de cada uma das colunas baseado na entrada 'n'
    {
        head_col[i] = ( Matrix * )malloc( sizeof( Matrix ) );
        head_col[i]->below = head_col[i];//----------------------->Faz a cabeça de cada coluna apontar para si própria
        head_col[i]->right = NULL;
        head_col[i]->column = -1;
    }

    head->right = head_col[0];//---------------------------------->Faz a cabeça principal apontar para a cabeça que repesenta a primeira coluna
    head->below = head_row[0];//---------------------------------->Faz a cabeça principal apontar para a cabeça que repesenta a primeira linha

    for ( i = 0; i < m - 1; i++ )//------------------------------->Faz a cabeça de cada linha apontar para a cabeça da linha de baixo
        head_row[i]->below = head_row[i+1];

    head_row[i]->below = head;//---------------------------------->Faz a última linha apontar para a cabeça

    for ( i = 0; i < n - 1; i++ )//------------------------------->Faz a cabeça de cada coluna apontar para a cabeça da coluna do lado
        head_col[i]->right = head_col[i+1];

    head_col[i]->right = head;//---------------------------------->Faz a última coluna apontar para a cabeça

    for ( ;; ) {
        flag = 0;
        do
        {
            if ( flag == 1 )//------------------------------------>Ao final do 'do while' o valor da flag é setado em '1', logo caso
                printf( "\nInvalid value, insert again!!" );//---- o 'do while' ocorra uma seguda vez, cairá nesse 'if' 

            printf( "\nEnter row, column, value: " );
            scanf( "%d %d %f", &i, &j, &value );
            flag = 1;
            getchar();
        } while ( i > m || j > n || i < 1 || j < 1 );

        if ( value == 0 )//--------------------------------------->A condição para sair do for é setar a variável 'value' em '0'
            break;

        matrix_setelem( head, i, j, value );//-------------------->Cria uma nova célula a partir da função 'matrix_setelem'
    }
    return head;
}

void matrix_print( Matrix *m ) {
    Matrix *currentRow = NULL;
    int nRows = 1, nCols = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRows++ );//->Conta a quantidade de linhas
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nCols++ );//->Conta a quantidade de colunas

    int curRow, curCol;
    float matrix[nRows][nCols];//--------------------------------------------------------------------->Cria uma matriz de nRows x nCols

    for ( curRow = 0; curRow <= nRows; curRow++ )//--------------------------------------------------->Inicializa todos o elementos da matriz em '0'
        for ( curCol = 0; curCol <= nCols; curCol++ )
            matrix[curRow][curCol] = 0;

    currentRow = m->below;//-------------------------------------------------------------------------->CurrentRow recebe a cabeça da primeira linha

    while ( currentRow != m )//----------------------------------------------------------------------->Reepete enquanto o currentRow não voltar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//---------------------------------------------------->CurrentCell recebe a primeira célula da linha
        
        while ( currentCell != currentRow )//--------------------------------------------------------->Repete enquanto o currentCell não voltar para a cabeça da linha
        {
            matrix[currentCell->row - 1][currentCell->column - 1] = currentCell->info;//-------------->A matriz criada recebe o valor que está na mesma posição da matriz esparsa
            currentCell = currentCell->right;//------------------------------------------------------->Vai para a próxima célula na mesma linha
        }

        currentRow = currentRow->below;//------------------------------------------------------------->Terminada a linha, pula para a próxima
    }

    for ( curRow = 0; curRow < nRows; curRow++ )//---------------------------------------------------->Printa a matriz esparsa com os '0's nas posições vazias
    {
        for ( curCol = 0; curCol < nCols; curCol++ )
        {
            if ( matrix[curRow][curCol] < 10 )//------------------------------------------------------>if desnecessário, foi apenas por estética
                printf( "(%d, %d): %.2f   ", ( curRow + 1 ), ( curCol + 1 ), matrix[curRow][curCol] );
            else
                printf( "(%d, %d): %.2f  ", ( curRow + 1 ), ( curCol + 1 ), matrix[curRow][curCol] );
        }
        printf( "\n" );//----------------------------------------------------------------------------->Pula um linha depois de percorrer o curCol
    }
}

void matrix_destroy( Matrix *m ) {
    Matrix *currentRow = m->below;//-------------------->Inicializa o currentRow com a primeira linha da matriz

    while ( currentRow != m )//------------------------->Repete enquanto currentRow não retornar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//------>CurrentCell recebe a primeira célula daquela linha

        while ( currentCell != currentRow )//----------->Repete enquanto o currentCell não retornar para a cabeça da linha atual
        {
            Matrix *temp = currentCell;
            temp->below = temp;
            currentCell = currentCell->right;
            currentRow->right = currentCell;
            free( temp );//----------------------------->Libera um a um todas as células daquela linha
        }

        Matrix *tempRow = currentRow;
        currentRow = currentRow->below;//--------------->currentRow recebe a cabeça da próxima linha
        free( tempRow );//------------------------------>Libera a cabeça da linha na qual todas as células já foram apagadas
    }

    Matrix *currentCol = m->right;//-------------------->Inicializa o currentCol com a primeira coluna da matriz

    while ( currentCol != m )//------------------------->Libera as cabeças da colunas da matriz
    {
        Matrix *tempCol = currentCol;
        currentCol = currentCol->right;
        free ( tempCol );
    }

    free( m );//---------------------------------------->Libera a cabeça principal da matriz

    printf("Matrix destroyed\n");
}

float matrix_getelem( Matrix *m, int x, int y )
{
    Matrix *currentRow = NULL;
    int nRows = 1, nCols = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRows++ );//->Conta a quantidade de linhas
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nCols++ );//->Conta a quantidade de colunas

    int curRow, curCol;
    float matrix[nRows][nCols];//--------------------------------------------------------------------->Cria uma matriz de nRows x nCols

    for ( curRow = 0; curRow <= nRows; curRow++ )//--------------------------------------------------->Inicializa todos o elementos da matriz em '0'
        for ( curCol = 0; curCol <= nCols; curCol++ )
            matrix[curRow][curCol] = 0;

    currentRow = m->below;//-------------------------------------------------------------------------->CurrentRow recebe a cabeça da primeira linha

    while ( currentRow != m )//----------------------------------------------------------------------->Reepete enquanto o currentRow não voltar para a cabeça principal
    {
        Matrix *currentCell = currentRow->right;//---------------------------------------------------->CurrentCell recebe a primeira célula da linha
        
        while ( currentCell != currentRow )//--------------------------------------------------------->Repete enquanto o currentCell não voltar para a cabeça da linha
        {
            matrix[currentCell->row - 1][currentCell->column - 1] = currentCell->info;//-------------->A matriz criada recebe o valor que está na mesma posição da matriz esparsa
            currentCell = currentCell->right;//------------------------------------------------------->Vai para a próxima célula na mesma linha
        }

        currentRow = currentRow->below;//------------------------------------------------------------->Terminada a linha, pula para a próxima
    }

    return matrix[x - 1][y - 1];//-------------------------------------------------------------------->Retorna o valor da célula na posição desejada
}
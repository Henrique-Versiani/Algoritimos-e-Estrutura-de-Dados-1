#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
	struct matrix *right;
	struct matrix *below;
	int rows;
	int column;
	float info;
}Matrix;

Matrix *matrix_create( void );
void matrix_print(Matrix* head);
void matrix_setelem( Matrix* m, int x, int y, float elem );

int main( void ) {

    Matrix *A = matrix_create();
    matrix_print(A);

    return 0;
}

void matrix_setelem( Matrix* m, int x, int y, float elem )
{
    int nRows = 1, nCols = 1;
    Matrix *new = ( Matrix * )malloc( sizeof( Matrix ) );
    new->rows = x;
    new->column = y;
    new->info = elem;

    Matrix *p, *q, *r, *s;
    for ( r = m->right; r != m && y != nCols; r = r->right, nCols++ );
    for ( s = m->below; s != m && x != nRows; s = s->below, nRows++ );

    for ( p = s; p->right != s && p->right->column < y; p = p->right );
    for ( q = r; q->below != r && q->below->rows < x; q = q->below );

    new->right = p->right;
    p->right = new;
    new->below = q->below;
    q->below = new;

    if ( ( p->right->right->rows == x && p->right->right->column == y ) )
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

    Matrix *head = ( Matrix * )malloc( sizeof( Matrix ) );

    head->rows = -1;
    head->column = -1;
    head->right = NULL;
    head->below = NULL;

    Matrix *head_row[m], *head_col[n];

    for ( i = 0; i < m; i++ )
    {
        head_row[i] = ( Matrix * )malloc( sizeof( Matrix ) );
        head_row[i]->right = head_row[i];
        head_row[i]->below = NULL;
        head_row[i]->rows = -1;
    }

    for ( i = 0; i < n; i++ )
    {
        head_col[i] = ( Matrix * )malloc( sizeof( Matrix ) );
        head_col[i]->below = head_col[i];
        head_col[i]->right = NULL;
        head_col[i]->column = -1;
    }

    head->right = head_col[0];
    head->below = head_row[0];

    for ( i = 0; i < m - 1; i++ )
        head_row[i]->below = head_row[i+1];

    head_row[i]->below = head;

    for ( i = 0; i < n - 1; i++ )
        head_col[i]->right = head_col[i+1];

    head_col[i]->right = head;

    for ( ;; ) {
        flag = 0;
        do
        {
            if ( flag == 1 )
                printf( "\nInvalid value, insert again!!" );

            printf( "\nEnter row, column, value: " );
            scanf( "%d %d %f", &i, &j, &value );
            flag = 1;
            getchar();
        } while ( i > m || j > n || i < 1 || j < 1 );

        if ( value == 0 )
            break;

        matrix_setelem( head, i, j, value );
    }
    return head;
}

void matrix_print( Matrix* head ) {
    Matrix* currentRow = head->below;

    while (currentRow != head) {
        Matrix* currentCell = currentRow->right;
        
        while ( currentCell != currentRow )
        {
            printf( "(%d, %d): %.2f   ", currentCell->rows, currentCell->column, currentCell->info );
            currentCell = currentCell->right;
        }
        
        printf( "\n" );
        currentRow = currentRow->below;
    }
}
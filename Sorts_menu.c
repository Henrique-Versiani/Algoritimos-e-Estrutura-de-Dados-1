#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int menu( void );
void Insertion_sort( int array[], int n );
void Selection_sort( int array[], int n );
void Merge_sort( int array[], int left, int right );
void Merge( int array[], int left, int middle, int right );
void Quick_sort( int array[], int left, int right );
void free_array( int array[], int n );
bool Order_verification( int array[], int n );

int main( void )
{
    clock_t start, end;
    double cpu_time_used;
    int mainmenu, i;
    int n;

    n = 100000;

    int *array = ( int * )malloc( sizeof( int ) * n );
    int *temp = ( int * )malloc( sizeof( int ) * n );

    srand( time( 0 ) );

    for( i = 0; i < n; i++ )
        array[i] = rand() % 1000;

    for( i = 0; i < n; i++ )
        temp[i] = array[i];

    for( ;; )
    {
        mainmenu = menu();
        switch( mainmenu )
        {
            case 1:
                start = clock();
                Insertion_sort( array, n );
                end = clock();
                break;
            case 2:
                start = clock();
                Selection_sort( array, n );
                end = clock();
                break;
            case 3:
                start = clock();
                Merge_sort( array, 0, ( n - 1 ) );
                end = clock();
                break;
            case 4:
                start = clock();
                Quick_sort( array, 0, ( n - 1 ) );
                end = clock();
                break;
            case 5:
                printf( "Quiting aplication..." );
                free( array );
                free( temp );
                exit( 0 );
        }
        cpu_time_used = ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC;
        printf( "Execution time: %f seconds\n", cpu_time_used );

        if( Order_verification( array, n ) )
            printf( "The order is correct\n" );
        else
            printf( "The order is incorrect\n" );

        for( i = 0; i < n; i++ )// Restaura o ordem do array antes do uso do sort
            array[i] = temp[i];
    }

    return 0;
}

int menu( void )
{
    int choice;
    do
    {
        printf( "\n\t\t--------MENU--------" );
        printf( "\n\t\t1: Insertion sort" );
        printf( "\n\t\t2: Selection sort" );
        printf( "\n\t\t3: Merge sort" );
        printf( "\n\t\t4: Quick sort" );
        printf( "\n\t\t5: Quit" );
        printf( "\n\t\tChoice: " );
        scanf( "%d", &choice );
        getchar();
    }while( choice < 1 || choice > 5);

    return choice;
}

void Insertion_sort( int array[], int n )
{
    int tmp, i, j;
    for( j = 1; j < n; j++ )
    {
        i = j - 1;
        tmp = array[j];
        while ( (i >= 0 ) && ( tmp < array[i] ) )
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = tmp;
    }
}

void Selection_sort( int array[], int n ){
    int min, temp, i, j, min_id;

    for( i = 0; i < n-1; i++ )
    {
        min = array[i];
        for( j = i + 1; j < n; j++ )
        {
            if( array[j] < min )
            {
                min = array[j];
                min_id = j;
            }
        }
        temp = array[i];
        array[i] = array[min_id];
        array[min_id] = temp;
        min_id = i + 1;
    }
}

void Merge_sort( int array[], int left, int right )
{
    if( left == right )
        return;

    int middle = left + ( right - left ) / 2 ;

    Merge_sort( array, left, middle );
    Merge_sort( array, ( middle + 1 ), right );
    Merge( array, left, middle, right );
}

void Merge( int array[], int left, int middle, int right )
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Cria arrays temporários
    int L[n1], R[n2];

    // Copia os dados para os arrays temporários L[] e R[]
    for ( i = 0; i < n1; i++ )
        L[i] = array[left + i];
    for ( j = 0; j < n2; j++ )
        R[j] = array[middle + 1 + j];

    // Mescla os arrays temporários de volta no array original array[l..r]
    i = 0; // Índice inicial do primeiro subarray
    j = 0; // Índice inicial do segundo subarray
    k = left; // Índice inicial do subarray mesclado
    while ( i < n1 && j < n2 )
    {
        if ( L[i] <= R[j] )
        {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver algum
    while ( i < n1 )
    {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver algum
    while ( j < n2 )
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

void Quick_sort( int array[], int left, int right )
{
    int mid, tmp, i, j;
    i = left;
    j = right;
    mid = array[( left + right ) / 2];

    do
    {
        while( array[i] < mid )
            i++;
        while( mid < array[j] )
            j--;
        if(i <= j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }while( i <= j );

    if( left < j )
        Quick_sort( array, left, j );
    if( i < right )
        Quick_sort( array, i, right );
}

bool Order_verification( int array[], int n )
{
    for( int i = 0; i < n - 1; i++ )
        if( array[i] > array[i + 1] )
            return false;
    
    return true;
}
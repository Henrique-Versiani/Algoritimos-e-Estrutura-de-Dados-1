#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int val;
}Preferences;

typedef struct TypeQueue{
    Preferences info;
    struct TypeQueue *pNext;
}TypeQueue;

typedef struct{
    TypeQueue *pFirst;
    TypeQueue *pLast;
}Queue;

Queue *RESET( Queue *pOldQueue );
void PUSH( Queue *pQueue, Preferences *pInfo );
int POP( Queue *pQueue, Preferences *pInfo);
void print( Queue *pQueue );
int countStudents(int *students, int studentsSize, int *sandwiches, int sandwichesSize);
Queue *freeQueue( Queue *pQueue );

int main()
{
    int students[] = {0,1,1,0,1,1,1,0,0};
    int sandwiches[] = {1,0,1,1,0,1,1,0,1};
    int stSize = 9, swSize = 9;

    int answer = countStudents( students, stSize, sandwiches, swSize );

    printf( "\n%d", answer );
    return 0;
}

Queue *RESET( Queue *pOldQueue )
{
    if( pOldQueue )
        free( pOldQueue );

    Queue *pQueue = ( Queue * ) malloc( sizeof ( Queue ) );
    pQueue->pFirst = NULL;
    pQueue->pLast = NULL;

    return pQueue;

}

void PUSH( Queue *pQueue, Preferences *pInfo )
{
    TypeQueue *new = ( TypeQueue * ) malloc( sizeof( TypeQueue ) );

    new->info = *pInfo;
    new->pNext = NULL;

    if( pQueue->pLast != NULL )
        pQueue->pLast->pNext = new; 
    else
        pQueue->pFirst = new;
     pQueue->pLast = new;

}

int POP( Queue *pQueue, Preferences *pInfo )
{
    TypeQueue *nodo;

    if( pQueue->pFirst == NULL )
    {
        printf( "\n------\nQueue is empty\n------\n" );
        return 0;
    }else{
        nodo = pQueue->pFirst;
        *pInfo = pQueue->pFirst->info;
        pQueue->pFirst = pQueue->pFirst->pNext;
    }
    if( pQueue->pFirst == NULL )
        pQueue->pLast = NULL;

    free( nodo );
    return 1;
}

Queue *freeQueue( Queue *pQueue )
{
    TypeQueue *nodo;

    while( pQueue->pFirst != NULL )
    {
        nodo = pQueue->pFirst;
        pQueue->pFirst = pQueue->pFirst->pNext;
        free( nodo );
    }
    if( pQueue->pFirst == NULL )
        pQueue->pLast = NULL;

    free( pQueue );
    return NULL;
}

int countStudents(int *students, int studentsSize, int *sandwiches, int sandwichesSize)
{
    int i;
    int flag = 0;
    Preferences num;
    Queue *stQueue = NULL;
    Queue *swQueue = NULL;
    stQueue = RESET( stQueue );
    swQueue = RESET( swQueue );

    for( i = 0; i < studentsSize; i++ )
    {
        num.val = students[i];
        PUSH( stQueue, &num );
        num.val = sandwiches[i];
        PUSH( swQueue, &num );
    }

    while( flag < studentsSize &&  studentsSize != 0 )
    {
        if( stQueue->pFirst->info.val == swQueue->pFirst->info.val )
        {
            flag = 0;
            studentsSize--;
            sandwichesSize--;
            POP( stQueue,&num );
            POP( swQueue, &num );
        }else{
            num = stQueue->pFirst->info;
            POP( stQueue, &num );
            PUSH( stQueue, &num);
            flag++;
        }
    }
    stQueue = freeQueue ( stQueue );
    swQueue = freeQueue ( swQueue );

    return studentsSize;
}
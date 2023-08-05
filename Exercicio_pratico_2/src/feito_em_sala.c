#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int val;
}Numbers;

typedef struct{
    Numbers info;
    struct TypeQueue *pNext;
}TypeQueue;

typedef struct{
    TypeQueue *pFirst;
    TypeQueue *pLast;
}Queue;

Queue *RESET( );
void PUSH( Queue *pQueue, Numbers *pProduct );
int POP( Queue *pQueue, Numbers *pProduct);
void print( Queue *pQueue );
int countStudents(int *students, int studentsSize, int *sandwiches, int sandwichesSize);

int main(){
    return 0;
}

Queue *RESET( ){
    Queue *pQueue = ( Queue * ) malloc( sizeof ( Queue ) );
    pQueue->pFirst = NULL;
    pQueue->pLast = NULL;

    return pQueue;
}

void PUSH( Queue *pQueue, Numbers *pProduct ){
    TypeQueue *new; 
    new = ( TypeQueue * ) malloc( sizeof( TypeQueue ) );

    new->info = *pProduct;
    new->pNext = NULL;

    if( pQueue->pLast != NULL ){
        pQueue->pLast->pNext = new;
    } else{
        pQueue->pFirst = new;
    }
     pQueue->pLast = new;

}

int POP( Queue *pQueue, Numbers *pProduct ){
    TypeQueue *nodo;

    if( pQueue->pFirst == NULL ){
        printf( "\n------\nQueue is empty\n------\n" );
        return 0;
    } else{
        nodo = pQueue->pFirst;
        *pProduct = pQueue->pFirst->info;
        pQueue->pFirst = pQueue->pFirst->pNext;
    }
    if( pQueue->pFirst == NULL ){
        pQueue->pLast = NULL;
    }

    free( nodo );
    return 1;
}

int countStudents(int *students, int studentsSize, int *sandwiches, int sandwichesSize){
    int i, save;
    int flag;
    Numbers num;
    Queue *stQueue = RESET( );
    Queue *swQueue = RESET( );
    for( i = 0; i < studentsSize; i++ ){
        num.val = students[i];
        PUSH( stQueue, &num );
        num.val = sandwiches[i];
        PUSH( swQueue, &num );
    }
    
    while( flag != studentsSize )
        if( stQueue->pFirst == swQueue->pFirst )
        {
            flag = 0;
            studentsSize--;
            sandwichesSize--;
            POP( stQueue,&num );
            POP( swQueue, &num );
        }
        else{
            save = stQueue->pFirst;
            POP( stQueue, &num );
            num.val = save;
            PUSH( stQueue, &num);
            flag++;
        }

    return studentsSize;
}
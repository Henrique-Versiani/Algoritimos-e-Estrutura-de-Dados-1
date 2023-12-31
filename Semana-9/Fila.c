#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char name[40];
    float price;
}Product;

typedef struct TypeQueue{
    Product info;
    struct TypeQueue *pNext;
}TypeQueue;

typedef struct{
    TypeQueue *pFirst;
    TypeQueue *pLast;
}Queue;

Queue *RESET( Queue *pOldQueue ){
    if( pOldQueue ){
        free( pOldQueue );
    }

    Queue *pQueue = ( Queue * ) malloc( sizeof ( Queue ) );
    pQueue->pFirst = NULL;
    pQueue->pLast = NULL;

    return pQueue;

}

void PUSH( Queue *pQueue, Product *pProduct ){
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

int POP( Queue *pQueue, Product *pProduct ){
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

void print( Queue *pQueue ){
    TypeQueue *nodo;

    if ( pQueue->pFirst == NULL){
        printf( "\n------\nQueue is empty\n------\n" );
    } else{
        for( nodo = pQueue->pFirst; nodo != NULL; nodo = nodo->pNext ){
            printf( "\n------\nID: %d\nName: %s\nPrice: %.2f\n------\n" , nodo->info.id, nodo->info.name, nodo->info.price);
        }
    }
}
int main(){

    int menu;
    Queue *newQueue = NULL;
    newQueue = RESET( newQueue );
    Product newP, removeP;

    do{
    printf( "\n------\nMENU\n------\n\n1. Push\n2. Pop\n3. Print\n4. Exit\nOption: " );
    scanf( "%d", &menu );
    getchar();

    switch( menu ){
        case 1:
            printf("ID: ");
            scanf( "%d", &newP.id );
            getchar();
            printf( "Name: ");
            fgets( newP.name, sizeof(newP.name), stdin );
            newP.name[strcspn(newP.name, "\n")] = '\0';
            printf("Price: ");
            scanf( "%f", &newP.price );
            PUSH( newQueue, &newP );
            break;
        case 2:
            if( POP( newQueue, &removeP ) ){
                printf("\n------\nProduct removed\n------\nID: %d\nName: %s\nPrice: %2.f", removeP.id, removeP.name, removeP.price);
            }
            break;
        case 3:
        print( newQueue );
        break;
        case 4:
        break;
    }
    } while ( menu != 4 );

    return 0;
}
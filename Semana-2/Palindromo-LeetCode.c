#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode{
      int val;
      struct ListNode *next, *prev;
}Node;

Node *create_list ( void )
{
    Node *head = ( Node * )malloc( sizeof( Node ) );
    head->next = NULL;
    head->prev = NULL;
    return head;
}

void insert_in_the_end ( int val, Node *list )
{
    Node *end, *new = ( Node * )malloc( sizeof( Node ) );
    for ( end = list; end->next != NULL; end = end->next );
    new->val = val;
    new->next = end->next;
    end->next = new;
    new->prev = end;
}

Node *delete_list ( Node *list )
{
    Node *p = list, *temp = NULL;
    while ( p != NULL ){
        temp = p->next;
        free( p );
        p = temp;
    }
    return NULL;
}
bool isPalindrome (  Node *list )
{
    Node *p, *q, *r;
    int cont = 0;
    for( p = list; p->next != NULL; p = p->next )
        cont++;
    for( q = p, r = list->next; q->prev != NULL && r != NULL; q = q->prev, r = r->next )
        if ( q->val == r->val )
            cont--;
    if ( cont == 0 )
        return true;
    else
        return false;
}

int main ( void )
{
    Node *list = create_list ( );
    int val;
    
    do{
        printf ( "\nInsert a value: ");
        scanf  ( "%d", &val );
        if ( val >= 0 )
        insert_in_the_end ( val, list );
    }while ( val >= 0 );

    if ( isPalindrome ( list ) == true )
        printf ( "\ntrue");
    else
        printf ( "\nfalse" );

    list = delete_list ( list );
    return 0;
}
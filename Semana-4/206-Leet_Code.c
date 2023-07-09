#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList( struct ListNode* head ){
    struct ListNode *headReverse = ( struct ListNode * )malloc( sizeof( struct ListNode ) );
    struct ListNode *curr = head;
    headReverse->next = NULL;

    while (curr != NULL)
    {
        struct ListNode *new = ( struct ListNode * )malloc( sizeof( struct ListNode ) );
        new->val = curr->val;
        new->next = headReverse->next;
        headReverse->next = new;
        curr = curr->next;
    }

    return headReverse->next;
}
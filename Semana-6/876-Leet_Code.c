struct ListNode* middleNode(struct ListNode* head){
    struct ListNode *middle, *aux;
    for ( middle = head, aux = head; aux != NULL && aux->next != NULL; middle = middle->next, aux = aux->next->next );
    return middle;
}
void imprimirLista (No *head, No *current){
    if(current -> next == head){
        printf("%d", current -> num);
        return;
    }
    imprimirLista(head, current -> next);
    printf("%d", current -> num);
}
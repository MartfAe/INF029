#include <stdio.h>
#include <stdlib.h>

int main(){
    int *ptr, valor;
    printf("Digite um valor:\n");
    scanf("%d", &valor);
    ptr= &valor;
    printf("Valor final pelo ponteiro: %d\n", *ptr);

    printf("Alterando o valor da variável por meio de um ponteiro...\n");
    printf("Digite um novo valor:");
    scanf("%d", ptr);
    printf("Novo valor da variável:%d", valor);
    return 0;



}
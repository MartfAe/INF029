#include <stdio.h>
#include<stdlib.h>

int main(){
    int v1, v2;

    printf("Digite dois valores:\n");
    scanf("%d", &v1);
    scanf("%d", &v2);
    int soma = v1 + v2;
    printf("Soma = %d", soma);
}
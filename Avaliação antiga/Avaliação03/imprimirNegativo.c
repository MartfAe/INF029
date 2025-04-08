#include <stdio.h>
#include <stdlib.h>

void imprimirNegativo(int n){
    if(n >0){
        return;
    }
    if(n%2 == 0){
        printf("%d\n", n);
    }
    imprimirNegativo(n+1);
}

int main(){
    int n;

    printf("Digite um numero inteiro:");
    scanf("%d", &n);

    imprimirNegativo(n);
    return 0;
}
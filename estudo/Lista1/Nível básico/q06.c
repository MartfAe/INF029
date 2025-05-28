#include <stdio.h>
#include <stdlib.h>

int main() {
    int v1;
    printf("Digite um numero:");
    scanf("%d", &v1);
    if(v1==0){
        printf("Numero = 0");
    }else if(v1<0){
        printf("Numero negativo.");
    }else{
        printf("Numero positivo");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    int v1, v2;
    printf("Digite dois valores:\n");
    scanf("%d", &v1);
    scanf("%d", &v2);
    if(v1>v2){
        printf("%d e o maior.", v1);
    }else if(v1<v2){
        printf("%d e o maior", v2);
    }else{
        printf("Numeros iguais");
    }
    return 0;
}
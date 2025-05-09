#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char palavra1[50];
    char palavra2[50];
    char palavra3[50];
}Palavras;

Palavras ler3Palavras(){
    Palavras p;

    printf("Digite a primeira palavra:");
    scanf("%s", p.palavra1);

    printf("Digite a segunda palavra:");
    scanf("%s", p.palavra2);

    printf("Digite a terceira palavra:");
    scanf("%s", p.palavra3);

    return p;
}

int main(){
    Palavras resultado =ler3Palavras;
    
    printf("\nAs palavras digitas foram:\n");
    printf("1: %s\n", resultado.palavra1);
    printf("2: %s\n", resultado.palavra2);
    printf("3: %s\n", resultado.palavra3);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    char palavra1[50];
    char palavra2[50];
    char palavra3[50];
}Palavras;

Palavras ler3Palavras(){
    Palavras lerPalavras;
    printf("Digite a primeira palavra:");
    scanf("%49s", lerPalavras.palavra1);

    printf("Digite a segunda palavra:");
    scanf("%49s", lerPalavras.palavra2);

    printf("Digite a terceira palavra:");
    scanf("%49s", lerPalavras.palavra3);
    return lerPalavras;
}

int main() {
    Palavras lerPalavras;

    lerPalavras = ler3Palavras();

    printf("---Palavras lidas---\n");

    printf("Primeira: %s\n", lerPalavras.palavra1);
    printf("Segunda:%s\n", lerPalavras.palavra2);
    printf("Terceira:%s\n", lerPalavras.palavra3);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char letra1;
    char letra2;
    char letra3;
}Letras;
//Ao criar uma função a partir de uma struct, dentro dela, a variável também vai ser do tipo da struct. 
Letras ler3Letras(){
    Letras lerLetras; 
    printf("Digite a primeira letra:");
    scanf("%c", &lerLetras.letra1);

    printf("Digite a segunda letra:");
    scanf(" %c", &lerLetras.letra2);

    printf("Digite a terceira letra:");
    scanf(" %c", &lerLetras.letra3);

    return lerLetras;
}
int main() {
    Letras lerLetras;
    //Lendo as letras. 
    lerLetras = ler3Letras();
    printf("Primeira letra lida: %c\n", lerLetras.letra1);
    printf("Segunda letra lida: %c\n", lerLetras.letra2);
    printf("Terceira letra lida: %c\n", lerLetras.letra3);

    return 0;
}
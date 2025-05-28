#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inverterString(char str[]){
    int tamanho = strlen(str);
    for(int i= tamanho-1; i >=0; i--){
        printf("%c", str[i]);
    }
}

int main() {
    char string[85];
    printf("Digite uma frase:");
    scanf("%[^\n]", string);
    printf("String invertida: ");
    inverterString(string);
    return 0;
}
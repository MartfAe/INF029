#include <stdio.h>
#include <stdlib.h>

void ler3Letras(char letras[]){
    for(int i =0; i <3; i++){
        printf("Digite a %d letra de 3:", i+1);
        scanf(" %c", &letras[i]);
    }

    printf("As letras informadas foram:");
    for(int i=0; i<3; i++){
        printf("%c ", letras[i]);
    }

}

int main(){
    char letras[3];
    ler3Letras(letras);
    return 0;
}
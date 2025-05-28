#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void organizarCaractereEspecial(char str[]){
    int strOriginal = 0;
    int strModificada =0 ;

    while(str[strOriginal]!='\0'){
        if(isalnum((unsigned char)str[strOriginal])){
            str[strModificada] = str[strOriginal];
            strModificada++;
        }
        strOriginal++;
    }
    str[strModificada]='\0';
}

int main(){
    char texto[]= "atençao";
    organizarCaractereEspecial(texto);
    printf("Saida: %s", texto);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>



int main(){

    int x, *ponteiroInt;
    char a, *ponteiroChar;
    float z, *ponteiroFloat;

    x= 10;
    a ='b';
    z= 3.5;

 
    ponteiroInt= &x;
    ponteiroChar = &a;
    ponteiroFloat = &z;
    
    printf("Valores iniciais: %d, %c, %.0f", x, a,z);

    printf("Digite um valor inteiro:");
    scanf("%d", ponteiroInt);

    printf("Digite um caractere:");
    scanf(" %c", ponteiroChar);

    printf("Digite um valor real:");
    scanf("%f", ponteiroFloat);

    printf("Valores atualizados:");
    printf("%d , %c, %f", x, a, z );

    return 0;


}
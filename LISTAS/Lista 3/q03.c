#include <stdio.h>
#include <stdlib.h>

int inverterNumero(int x, int invertido);

int main (){
    int numero, resultado;

    printf("Digite um número inteiro:");
    scanf("%d", &numero);

    resultado = inverterNumero(numero, 0);

    printf("O número invertido é %d\n", resultado);

    return 0;
}

int inverterNumero(int x, int invertido){
    if( x ==0){
        return invertido;
    }
    return inverterNumero(x/10 , invertido*10 + x%10);

}
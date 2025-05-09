#include <stdio.h>
#include <stdlib.h> 

int soma(int valor1, int valor2){
    int soma;
    soma = valor1 + valor2;
    
    return(soma);
    
}

int main(){
    int v1, v2, adicao;
    printf("Digite um valor:");
    scanf("%d", &v1);
    printf("Digite outro valor:");
    scanf("%d", &v2);
    adicao=soma(v1,v2);
    printf("A soma total foi: %d", adicao);
    return (0);


}
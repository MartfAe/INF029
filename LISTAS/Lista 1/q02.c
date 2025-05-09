#include <stdio.h>
#include <stdlib.h>

int subtrai(int valor1, int valor2, int valor3){
   int subtracao = valor1-valor2-valor3;
    return(subtracao);
}

int main(){
    int n1, n2,n3, sub;
    printf("Digite o primeiro valor:");
    scanf("%d", &n1);
    printf("Digite o segundo valor:");
    scanf("%d", &n2);
    printf("Digite o ultimo valor:");
    scanf("%d", &n3);
    sub=subtrai(n1,n2,n3);
    printf("O valor final da subtração foi:%d", sub);
    return 0;

}
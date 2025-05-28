#include <stdio.h>
#include <stdlib.h>

int soma(int v1, int v2){
    int adicao = v1 + v2;
    return adicao;
}

int main() {
    int v1, v2;
    printf("Digite dois valores:\n");
    scanf("%d", &v1);
    scanf("%d", &v2);
    int resultado = soma(v1, v2);
    printf("Soma = %d", resultado);
    return 0;
}
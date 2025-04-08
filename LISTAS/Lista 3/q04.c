#include <stdio.h>
#include <stdlib.h>

int somaVetor(int vetor[], int x, int y){
    int = soma;
    if(x == y){
        return vetor[x];
    }

    soma = v[i] + somaVetor(vetor, x+1, y);
    return soma;
}


int main(){

    int n;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int *vetor = (int*)malloc(n*sizeof(int));
    if(vetor == NULL){
        printf("Memória insuficiente\n");
        return 1;
    }

    printf("Digite os elementos do vetor: ");
    for (int i =0; i <n; i++){
        scanf("%d", &vetor[i]);
        
    }
}